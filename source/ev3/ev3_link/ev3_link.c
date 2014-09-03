/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  ev3_link.c
 *  \brief  EV3 remote access.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  The MIT License
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
#define socklen_t int32_t
#include <winsock.h>
#include <wininet.h>

#define bzero( ptr, sz ) memset( ptr, 0, sz )

// UNIX //////////////////////////////////////////
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

#include "ev3_link.h"

#define PROGRAM  "ev3_link"

#define UDP_MESSAGE_LIMIT  1500

#define UDP_RECEIVE_TRIES  50
#define UDP_RECEIVE_WAIT   10  /* msec */
#define UDP_TRANSMIT_TRIES 2

enum {
	EV3_NONE,

	EV3_WRITE_FILE,
	EV3_RESULT_WRITE,

	EV3_READ_FILE,
	EV3_DATA_READ,

	EV3_LIST_DIR,
	EV3_DIRECTORY,

	EV3_POWEROFF,
	EV3_COMPLETION,
};

typedef struct {
	uint16_t type;
	uint16_t id;
	uint16_t fn_size;
	uint16_t data_size;
} EV3_MESSAGE_HEADER, *PEV3_MESSAGE_HEADER;

typedef struct {
	EV3_MESSAGE_HEADER head;
	char body[ UDP_MESSAGE_LIMIT - sizeof( EV3_MESSAGE_HEADER )];
} EV3_MESSAGE, *PEV3_MESSAGE;

static int sockfd;
static EV3_MESSAGE __r_msg;
static EV3_MESSAGE __t_msg;
static struct sockaddr_in __r_addr, __t_addr;

// EV3 BOARD /////////////////////////////////////
#ifdef __ARM_ARCH_4T__

static size_t __ev3_write_binary( char *fn, void *data, size_t sz )
{
	FILE *f;
	size_t result;

	f = fopen( fn, "w" );
	if ( f == NULL ) {
		printf( "*** ERROR *** (ev3_link) fopen(%s): %s\n", fn, strerror( errno ));
		return ( 0 );
	}
	result = fwrite( data, 1, sz, f );
	fclose( f );

	return ( result );
}

static size_t __ev3_read_binary( char *fn, void *buf, size_t sz )
{
	FILE *f;
	size_t result;

	f = fopen( fn, "r" );
	if ( f == NULL ) {
		printf( "*** ERROR *** (ev3_link) fopen(%s): %s\n", fn, strerror( errno ));
		return ( 0 );
	}
	result = fread( buf, 1, sz, f );
	fclose( f );

	return ( result );
}

static size_t __ev3_listdir( char *fn, void *buf, size_t sz )
{
	DIR *d;
	struct dirent *de;
	char *p;

	d = opendir( fn );
	if ( d == NULL ) return ( 0 );

	p = buf;
	while (( de = readdir( d ))) {
		int l = strlen( de->d_name ) + 1;
		if ( sz > l ) {
			sz -= l;
			memcpy( p, de->d_name, l - 1 );
			p[ l - 1 ] = ' ';
			p += l;
		}
	}
	closedir( d );

	return (( void *) p - buf );
}

// CLIENT ////////////////////////////////////////
#else

static uint16_t __t_last = 0;

//////////////////////////////////////////////////
#endif

int udp_ev3_open( char *addr, uint16_t port )
{
	int val = 1;

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
	WSADATA wsa;
	int res = WSAStartup( MAKEWORD( 2, 2 ), &wsa );
	if ( res ) {
		printf( "\n*** ERROR *** udp_ev3_open() = %d\n", res );
		perror( "    WSAStartup()" );
		printf( "\n" );

		return ( 0 );
	}

//////////////////////////////////////////////////
#endif

	sockfd = socket( PF_INET, SOCK_DGRAM, 0 );
	if ( sockfd < 0 ) {
		printf( "\n*** ERROR *** udp_ev3_open() = %d\n", sockfd );
		perror( "    socket()" );
		printf( "\n" );
		sockfd = 0;

		return ( 0 );
	}
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
	setsockopt( sockfd, SOL_SOCKET, SO_BROADCAST, ( const char *) &val, sizeof( val ));
	u_long opt = 1;
	ioctlsocket( sockfd, FIONBIO, &opt );

// UNIX //////////////////////////////////////////
#else
	setsockopt( sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof( val ));
	fcntl( sockfd, F_SETFL, O_NONBLOCK );

//////////////////////////////////////////////////
#endif

	bzero( &__r_addr, sizeof( struct sockaddr_in ));
	__r_addr.sin_family = AF_INET;
	__r_addr.sin_port = htons( port );
	__r_addr.sin_addr.s_addr = htonl( INADDR_ANY );

	int ret = bind( sockfd, ( struct sockaddr *) &__r_addr, sizeof( __r_addr ));
	if ( ret < 0 ) {
		close( sockfd );
		printf( "\n*** ERROR *** udp_ev3_open() = %d\n", ret );
		perror( "    bind()" );
		printf( "\n" );
		sockfd = 0;

		return ( 0 );
	}
	bzero( &__t_addr, sizeof( struct sockaddr_in ));
	__t_addr.sin_family = AF_INET;
	__t_addr.sin_port = htons( port );
	__t_addr.sin_addr.s_addr = inet_addr( addr );

	return ( 1 );
}

static void __transmit( uint16_t sz )
{
	int res, l;

	l = sizeof( EV3_MESSAGE_HEADER ) + sz;
	res = sendto( sockfd, (const char *) &__t_msg, l, 0, ( struct sockaddr * ) &__t_addr, sizeof( __t_addr ));
	if ( res != l ) {
		printf( "\n*** ERROR *** (ev3_link) transmit: sendto = %d\n", errno );
		perror( "    sendto()" );
		printf( "\n" );
	}
}

static int __receive( void )
{
	int msg_l;
	socklen_t addr_l = sizeof( struct sockaddr_in );

	msg_l = recvfrom( sockfd, (char *) &__r_msg, sizeof( __r_msg ), 0, ( struct sockaddr * ) &__r_addr, &addr_l );
	if ( msg_l > 0 ) {
		PEV3_MESSAGE_HEADER h = &__r_msg.head;
		PEV3_MESSAGE_HEADER t = &__t_msg.head;

		if ( msg_l < ( int ) sizeof( EV3_MESSAGE_HEADER )) {
			printf( "\n*** ERROR *** (ev3_link) receive: HEADER: msg_l = %d\n", msg_l );

			return ( EOF );
		}
		msg_l -= sizeof( EV3_MESSAGE_HEADER );

		switch ( h->type ) {

// EV3 BOARD /////////////////////////////////////
#ifdef __ARM_ARCH_4T__

		case EV3_WRITE_FILE:
		case EV3_READ_FILE:
		case EV3_LIST_DIR:

			__t_addr.sin_addr.s_addr = __r_addr.sin_addr.s_addr;

			if (( h->fn_size == 0 ) || ( msg_l < ( int ) h->fn_size )) {
				printf( "*** ERROR *** (ev3_link) receive: FILE: msg_l = %d fn_size = %d\n", msg_l, h->fn_size );

				return ( EOF );
			}
			msg_l -= h->fn_size;
			__r_msg.body[ h->fn_size - 1 ] = '\x00';
			t->fn_size = 0;
			t->id = h->id;

			if ( h->type == EV3_WRITE_FILE ) {
				if (( h->data_size == 0 ) || ( msg_l != ( int ) h->data_size )) {
					printf( "*** ERROR *** (ev3_link) receive: DATA: msg_l = %d data_size = %d\n"
					, msg_l, h->data_size );

					return ( EOF );
				}
				/* printf( "WRITE %s\n", __r_msg.body ); */
				t->type = EV3_RESULT_WRITE;
				t->data_size = __ev3_write_binary( __r_msg.body, __r_msg.body + h->fn_size, h->data_size );
				__transmit( 0 );

				return ( h->type );
			}
			if (( h->data_size == 0 ) || (( int ) h->data_size > sizeof( __t_msg.body ))) {
				printf( "*** ERROR *** (ev3_link) receive: DATA: data_size = %d\n", h->data_size );

				return ( EOF );
			}
			if ( h->type == EV3_LIST_DIR ) {
				/* printf( "LIST %s\n", __r_msg.body ); */
				t->type = EV3_DIRECTORY;
				t->data_size = __ev3_listdir( __r_msg.body, __t_msg.body, h->data_size );
			} else {
				/* printf( "READ %s\n", __r_msg.body ); */
				t->type = EV3_DATA_READ;
				t->data_size = __ev3_read_binary( __r_msg.body, __t_msg.body, h->data_size );
			}
			__transmit( t->data_size );

			return ( h->type );

		case EV3_POWEROFF:

			__t_addr.sin_addr.s_addr = __r_addr.sin_addr.s_addr;

			if (( h->fn_size != 0x55 ) || ( h->data_size != 0xAA )) {

				return ( EOF );
			}
			t->id = h->id;
			t->fn_size = 0;
			t->data_size = 0;
			t->type = EV3_COMPLETION;
			__transmit( 0 );

			system( "shutdown -h now" );

			return ( h->type );

// CLIENT ////////////////////////////////////////
#else
		case EV3_DATA_READ:
		case EV3_DIRECTORY:
			( void ) t;
			if ( msg_l != ( int ) h->data_size ) {
				printf( "\n*** ERROR *** (ev3_link) receive: DATA: msg_l = %d data_size = %d\n", msg_l, h->data_size );
				return ( EOF );
			}
			return ( h->type );

		case EV3_RESULT_WRITE:
		case EV3_COMPLETION:

			return ( h->type );

//////////////////////////////////////////////////
#endif
		}
	}
	return ( EV3_NONE );
}

// EV3 BOARD /////////////////////////////////////
#ifdef __ARM_ARCH_4T__

static uint16_t port = 8800;
static int alive = 1;

static void __sig_handler( int sig )
{
	alive = 0;
}

int main( int argc, char **argv )
{
	struct sigaction sigint;

	if ( argc > 1 ) {
		char *end;
		int val = strtol( argv[ 1 ], &end, 0 );
		if (( *end == '\x00' ) && ( val > 0 ) && ( val < USHRT_MAX )) {
			port = val;
		} else {
			printf( "\nUsage: " PROGRAM " [port]\n" );

			return ( 2 );
		}
	}
	printf( "\n*** ( " PROGRAM " ) Hello! ***\n" );

	if ( !udp_ev3_open( "", port )) return ( 1 );

	sigint.sa_handler = __sig_handler;
	sigemptyset( &sigint.sa_mask );
	sigint.sa_flags = 0;
	sigaction( SIGINT, &sigint, NULL );

	while ( alive ) {
		usleep( 100 );
		__receive();
	}
	printf( "\n*** ( " PROGRAM " ) Bye! ***\n" );

	return ( 0 );
}

// CLIENT ////////////////////////////////////////
#else

static int __wait_reply( void )
{
	int i;

	for ( i = 0; i < UDP_RECEIVE_TRIES; i++ ) {
		Sleep( UDP_RECEIVE_WAIT );

		switch ( __receive()) {
		case EOF:
			/* ERROR */
			return ( 0 );

		case EV3_RESULT_WRITE:
		case EV3_DATA_READ:
		case EV3_DIRECTORY:
		case EV3_COMPLETION:
			if ( __t_msg.head.id == __r_msg.head.id ) return ( 1 );
			break;
		}
	}
	return ( 0 );
}

int udp_ev3_write( char *fn, void *data, int sz )
{
	PEV3_MESSAGE_HEADER t = &__t_msg.head;
	int i;

	t->type = EV3_WRITE_FILE;
	t->id = ++__t_last;
	t->fn_size = strlen( fn ) + 1;
	t->data_size = sz;
	memcpy( __t_msg.body, fn, t->fn_size );
	memcpy( __t_msg.body + t->fn_size, data, t->data_size );
	for ( i = 0; i < UDP_TRANSMIT_TRIES; i++ ) {
		__transmit( t->fn_size + t->data_size );
		if ( __wait_reply()) {

			return ( __r_msg.head.data_size );
		}
	}
	return ( 0 );
}

static int __udp_ev3_read( int cmd, char *fn, void *buf, int sz )
{
	PEV3_MESSAGE_HEADER h = &__t_msg.head;
	int i;

	h->type = cmd;
	h->id = ++__t_last;
	h->fn_size = strlen( fn ) + 1;
	h->data_size = sz;
	memcpy( __t_msg.body, fn, h->fn_size );
	for ( i = 0; i < UDP_TRANSMIT_TRIES; i++ ) {
		__transmit( h->fn_size );
		if ( __wait_reply()) {
			memcpy( buf, __r_msg.body, __r_msg.head.data_size );

			return ( __r_msg.head.data_size );
		}
	}
	return ( 0 );
}

int udp_ev3_read( char *fn, void *buf, int sz )
{
	return __udp_ev3_read( EV3_READ_FILE, fn, buf, sz );
}

int udp_ev3_listdir( char *fn, void *buf, int sz )
{
	return __udp_ev3_read( EV3_LIST_DIR, fn, buf, sz );
}

int udp_ev3_poweroff( void )
{
	PEV3_MESSAGE_HEADER h = &__t_msg.head;
	int i;

	h->type = EV3_POWEROFF;
	h->id = ++__t_last;
	h->fn_size = 0x55;
	h->data_size = 0xAA;
	for ( i = 0; i < UDP_TRANSMIT_TRIES; i++ ) {
		__transmit( 0 );
		if ( __wait_reply()) {

			return ( 1 );
		}
	}
	return ( 0 );
}

//////////////////////////////////////////////////
#endif
