/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  ev3_link.c
 *  \brief  EV3 remote access.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdlib.h>
#include <signal.h>
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
#include "../ev3_both.h"

/**
 *  \addtogroup ev3_link
 *  \{
 */

#define UDP_MESSAGE_LIMIT    1500

#define UDP_CLIENT_RX_TRIES  50
#define UDP_CLIENT_RX_WAIT   10    /* ms */
#define UDP_CLIENT_TX_TRIES  2

#define UDP_SERVER_RX_DELAY  1000  /* us */
#define UDP_SERVER_TX_DELAY  2000000

enum {
	EV3_IDLE         = 0,

	EV3_WRITE_FILE   = 1,  /**< File write command. */
	EV3_RESULT_WRITE = 2,  /**< Write result reply. */

	EV3_READ_FILE    = 3,  /**< File read command. */
	EV3_DATA_READ    = 4,  /**< Read data reply. */

	EV3_LIST_DIR     = 5,  /**< List directory command. */
	EV3_DIRECTORY    = 6,  /**< List directory reply. */

	EV3_POWEROFF     = 7,  /**< Power-off the brick command. */
	EV3_COMPLETION   = 8,  /**< Completion of work reply. */

	EV3_WELCOME      = 9,  /**< A broadcast beacon. */

	EV3_READ_KEYS    = 10, /**< Keys read command. */
	EV3_KEYS         = 11, /**< Keys reply. */

	EV3_MULTI_WRITE  = 12, /**< Multi files write command. */
};

/**
 *  \brief Header of an UDP message.
 */
typedef struct {
	uint16_t type;       /**< Command type. */
	uint16_t id;         /**< Message counter. */
	uint16_t fn_size;    /**< Filename size. */
	uint16_t data_size;  /**< Data size. */
} EV3_MESSAGE_HEADER, *PEV3_MESSAGE_HEADER;

/**
 *  \brief Sub-header for EV3_MULTI_WRITE.
 */
typedef struct {
	uint8_t  sn[ DESC_VEC_LEN ];  /**< Vector of sequence numbers. */
	uint16_t pos;                 /**< Position of the sequence number field into the filename. */
} EV3_MULTI_WRITE_SUBHEADER, *PEV3_MULTI_WRITE_SUBHEADER;

/**
 *  \brief UDP message.
 */
typedef struct {
	EV3_MESSAGE_HEADER head;
	char body[ UDP_MESSAGE_LIMIT - sizeof( EV3_MESSAGE_HEADER )];
} EV3_MESSAGE, *PEV3_MESSAGE;

static int sockfd;
static EV3_MESSAGE __r_msg;
static EV3_MESSAGE __t_msg;
static struct sockaddr_in __r_addr, __t_addr;

#define EOL       "\n"
#define ERR_PREF  "*** ERROR *** ev3_link: "

// EV3 BRICK /////////////////////////////////////
#ifdef __ARM_ARCH_4T__

#include <linux/input.h>
#include <sys/stat.h>
#include <syslog.h>
#include "modp_numtoa.h"

/* logging requires `apt-get install inetutils-syslogd`
 */
#define ERR_OUT( F, ... ) do { \
	syslog( LOG_ERR, F, ## __VA_ARGS__ ); \
} while ( 0 )

#define ERRNO_OUT( F, ... ) do { \
	int _err = errno; \
	syslog( LOG_ERR, F ": %s (%d)", ## __VA_ARGS__, strerror( _err ), _err ); \
} while ( 0 )

#define DEBUG_OUT( F, ... ) do { \
	syslog( LOG_DEBUG, F, ## __VA_ARGS__ ); \
} while ( 0 )

static size_t __ev3_write_binary( char *fn, char *data, size_t sz )
{
	FILE *f;
	size_t result;

	f = fopen( fn, "w" );
	if ( f == NULL ) {
		ERRNO_OUT( "write: fopen(%s)", fn );
		return ( 0 );
	}
	result = fwrite( data, 1, sz, f );
	fclose( f );
	return ( result );
}

static size_t __ev3_multi_write_binary( uint8_t *sn, uint16_t pos, char *fn, char *data, size_t sz )
{
	int i = 0;
	size_t result = 0;

	while (( i < DESC_VEC_LEN ) && ( sn[ i ] < DESC_LIMIT )) {
		*modp_uitoa10( sn[ i ], fn + pos ) = '/';
		result = __ev3_write_binary( fn, data, sz );
		if ( result == 0 ) return ( 0 );
		i++;
	}
	return ( result );
}

static size_t __ev3_read_binary( char *fn, char *buf, size_t sz )
{
	FILE *f;
	size_t result;

	f = fopen( fn, "r" );
	if ( f == NULL ) {
		ERRNO_OUT( "read: fopen(%s)", fn );
		return ( 0 );
	}
	result = fread( buf, 1, sz, f );
	fclose( f );
	return ( result );
}

#define _TEST_KEY( K, R )  (( keyb[ KEY_##K >> 3 ] & ( 1 << ( KEY_##K & 7 ))) ? 0 : EV3_KEY_##R )

size_t __ev3_read_keys( uint8_t *buf )
{
	int f;
	uint8_t keyb[( KEY_MAX + 7 ) / 8 ];

	f = open( GPIO_KEYS_PATH, O_RDONLY );
	if ( f < 0 ) return ( 0 );

	ioctl( f, EVIOCGKEY( sizeof( keyb )), &keyb );

	*buf = _TEST_KEY( UP, UP )        | _TEST_KEY( DOWN, DOWN )
	     | _TEST_KEY( LEFT, LEFT )    | _TEST_KEY( RIGHT, RIGHT )
	     | _TEST_KEY( ENTER, CENTER ) | _TEST_KEY( BACKSPACE, BACK );

	close( f );
	return ( sizeof( uint8_t ));
}

#undef _TEST_B

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

#define ERR_OUT( F, ... ) do { \
	printf( EOL ERR_PREF F EOL, ## __VA_ARGS__ ); \
} while ( 0 )

#define ERRNO_OUT( F, ... ) do { \
	int e = errno; \
	printf( EOL ERR_PREF F ": %s (%d)" EOL, ## __VA_ARGS__, strerror( e ), e ); \
} while ( 0 )

static uint16_t __t_last = 0;

//////////////////////////////////////////////////
#endif

int udp_ev3_open( char *addr, uint16_t port )
{
	u_long optval = 1;
	int res;

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
	WSADATA wsa;
	res = WSAStartup( MAKEWORD( 2, 2 ), &wsa );
	if ( res ) {
		ERRNO_OUT( "open: WSAStartup()" );
		sockfd = EOF;
		return ( EOF );
	}

//////////////////////////////////////////////////
#endif
	sockfd = socket( PF_INET, SOCK_DGRAM, 0 );
	if ( sockfd < 0 ) {
		ERRNO_OUT( "open: socket()" );
		sockfd = EOF;

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
		WSACleanup();

//////////////////////////////////////////////////
#endif
		return ( EOF );
	}
	bzero( &__r_addr, sizeof( struct sockaddr_in ));
	__r_addr.sin_family = AF_INET;
	__r_addr.sin_port = htons( port );
	__r_addr.sin_addr.s_addr = htonl( INADDR_ANY );

	res = bind( sockfd, ( struct sockaddr *) &__r_addr, sizeof( __r_addr ));
	if ( res < 0 ) {
		ERRNO_OUT( "open: bind()" );

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
		closesocket( sockfd );
		WSACleanup();

// UNIX //////////////////////////////////////////
#else
		close( sockfd );

//////////////////////////////////////////////////
#endif
		sockfd = EOF;
		return ( EOF );
	}

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
	setsockopt( sockfd, SOL_SOCKET, SO_BROADCAST, ( const char *) &optval, sizeof( optval ));
	ioctlsocket( sockfd, FIONBIO, &optval );

// UNIX //////////////////////////////////////////
#else
	setsockopt( sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof( optval ));
	fcntl( sockfd, F_SETFL, O_NONBLOCK );

//////////////////////////////////////////////////
#endif
	bzero( &__t_addr, sizeof( struct sockaddr_in ));
	__t_addr.sin_family = AF_INET;
	__t_addr.sin_port = htons( port );
	__t_addr.sin_addr.s_addr = ( addr ) ? inet_addr( addr ) : htonl( -1 );
	return ( 0 );
}

int udp_ev3_close( void )
{
	if ( sockfd < 0 ) return ( EOF );

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
	closesocket( sockfd );
	WSACleanup();

// UNIX //////////////////////////////////////////
#else
	close( sockfd );

//////////////////////////////////////////////////
#endif
	return ( 0 );
}

static void __transmit( uint16_t sz )
{
	int res, l;

	l = sizeof( EV3_MESSAGE_HEADER ) + sz;
	res = sendto( sockfd, ( const char *) &__t_msg, l, 0, ( struct sockaddr *) &__t_addr, sizeof( __t_addr ));
	if ( res < 0 ) {
		ERRNO_OUT( "transmit: sendto()" );
	}
}

static int __receive( void )
{
	int msg_l;
	char *fn;
	socklen_t addr_l = sizeof( struct sockaddr_in );

	msg_l = recvfrom( sockfd, ( char *) &__r_msg, sizeof( __r_msg ), 0, ( struct sockaddr *) &__r_addr, &addr_l );
	if ( msg_l > 0 ) {
		PEV3_MESSAGE_HEADER h = &__r_msg.head;
		PEV3_MESSAGE_HEADER t = &__t_msg.head;

		if ( msg_l < ( int ) sizeof( EV3_MESSAGE_HEADER )) {
			ERR_OUT( "receive: HEADER: msg_l = %d", msg_l );
			return ( EOF );
		}
		msg_l -= sizeof( EV3_MESSAGE_HEADER );
		fn = ( char *) __r_msg.body;

		switch ( h->type ) {

// EV3 BRICK /////////////////////////////////////
#ifdef __ARM_ARCH_4T__

		case EV3_MULTI_WRITE:
			if ( msg_l < ( int ) sizeof( EV3_MULTI_WRITE_SUBHEADER )) {
				ERR_OUT( "receive: SUBHEADER: msg_l = %d", msg_l );
				return ( EOF );
			}
			msg_l -= sizeof( EV3_MULTI_WRITE_SUBHEADER );
			fn += sizeof( EV3_MULTI_WRITE_SUBHEADER );
			/* fallthrough */

		case EV3_WRITE_FILE:
		case EV3_READ_FILE:
		case EV3_LIST_DIR:
			__t_addr.sin_addr.s_addr = __r_addr.sin_addr.s_addr;

			if (( h->fn_size == 0 ) || ( msg_l < ( int ) h->fn_size )) {
				ERR_OUT( "receive: FILE: msg_l = %d fn_size = %d", msg_l, h->fn_size );
				return ( EOF );
			}
			msg_l -= h->fn_size;
			t->fn_size = 0;
			t->id = h->id;
			fn[ h->fn_size - 1 ] = '\x00';  /* Restrict filename length */

			switch ( h->type ) {

			case EV3_MULTI_WRITE:
			case EV3_WRITE_FILE:
				if (( h->data_size == 0 ) || ( msg_l != ( int ) h->data_size )) {
					ERR_OUT( "receive: DATA: msg_l = %d data_size = %d", msg_l, h->data_size );
					return ( EOF );
				}
				if ( h->type == EV3_WRITE_FILE ) {
					DEBUG_OUT( "WRITE %s", __r_msg.body );
					t->data_size = __ev3_write_binary( __r_msg.body, __r_msg.body + h->fn_size, h->data_size );
				} else {
					PEV3_MULTI_WRITE_SUBHEADER sub = ( void *) __r_msg.body;
					DEBUG_OUT( "MULTI WRITE %s", fn );
					t->data_size = __ev3_multi_write_binary( sub->sn, sub->pos, fn, fn + h->fn_size, h->data_size );
				}
				t->type = EV3_RESULT_WRITE;
				__transmit( 0 );
				return ( h->type );

			case EV3_READ_FILE:
			case EV3_LIST_DIR:
				if (( h->data_size == 0 ) || (( int ) h->data_size > sizeof( __t_msg.body ))) {
					ERR_OUT( "receive: DATA: data_size = %d", h->data_size );
					return ( EOF );
				}
				if ( h->type == EV3_LIST_DIR ) {
					DEBUG_OUT( "LIST %s", __r_msg.body );
					t->type = EV3_DIRECTORY;
					t->data_size = __ev3_listdir( __r_msg.body, __t_msg.body, h->data_size );
				} else {
					DEBUG_OUT( "READ %s", __r_msg.body );
					t->type = EV3_DATA_READ;
					t->data_size = __ev3_read_binary( __r_msg.body, __t_msg.body, h->data_size );
				}
				__transmit( t->data_size );
				return ( h->type );
			}

		case EV3_READ_KEYS:
			__t_addr.sin_addr.s_addr = __r_addr.sin_addr.s_addr;
			DEBUG_OUT( "READ KEYS" );
			t->id = h->id;
			t->fn_size = 0;
			t->data_size = __ev3_read_keys(( uint8_t *) __t_msg.body );
			t->type = EV3_KEYS;
			__transmit( t->data_size );
			return ( h->type );

		case EV3_POWEROFF:
			__t_addr.sin_addr.s_addr = __r_addr.sin_addr.s_addr;

			if (( h->fn_size != 0x5555 ) || ( h->data_size != 0xAAAA )) {
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
		case EV3_KEYS:
			( void ) t;   /* unused */
			( void ) fn;  /* unused */
			if ( msg_l != ( int ) h->data_size ) {
				ERR_OUT( "receive: DATA: msg_l = %d data_size = %d", msg_l, h->data_size );
				return ( EOF );
			}
			return ( h->type );

		case EV3_RESULT_WRITE:
		case EV3_COMPLETION:
		case EV3_WELCOME:
			return ( h->type );

//////////////////////////////////////////////////
#endif
		}
	}
	return ( EV3_IDLE );
}

// EV3 BRICK /////////////////////////////////////
#ifdef __ARM_ARCH_4T__

static uint16_t port = 8800;
static int alive = 1;

static void __sig_handler( int sig )
{
	alive = 0;
}

void __welcome( void )
{
	PEV3_MESSAGE_HEADER t = &__t_msg.head;

	t->type = EV3_WELCOME;
	t->id = 0;
	t->fn_size = 0;
	t->data_size = 0;
	__transmit( 0 );
}

int main( int argc, char **argv )
{
	pid_t pid;
	struct sigaction sigint;
	uint32_t i = 0;

	if ( argc > 1 ) {
		char *end;
		int val = strtol( argv[ 1 ], &end, 0 );
		if (( *end == '\x00' ) && ( val > 0 ) && ( val < USHRT_MAX )) {
			port = val;
		} else {
			printf( EOL ERR_PREF "main: wrong argument" EOL );
			printf( "Usage: ev3_link [port]" EOL );
			return ( 2 );
		}
	}

	pid = fork();  /* fork parent process */
	if ( pid < 0 ) {
		printf( EOL ERR_PREF "main: fork(): unsuccessful" EOL );
		return ( 1 );
	}
	if ( pid > 0 ) return ( 0 );  /* exit parent process */

	umask( 0 );

	setlogmask( LOG_UPTO( LOG_NOTICE ));
	openlog( "ev3_link", LOG_PID, LOG_DAEMON );

	if ( setsid() < 0 ) {
		ERRNO_OUT( "main: setsid()" );
		closelog();
		return ( 1 );
	}
	chdir( "/" );
	/* close standard file descriptors */
	close( STDIN_FILENO );
	close( STDOUT_FILENO );
	close( STDERR_FILENO );

	if ( udp_ev3_open( NULL, port ) == EOF ) {
		closelog();
		return ( 1 );
	}
	sigint.sa_handler = __sig_handler;
	sigemptyset( &sigint.sa_mask );
	sigint.sa_flags = 0;
	sigaction( SIGINT, &sigint, NULL );

	while ( alive ) {
		usleep( UDP_SERVER_RX_DELAY );
		__receive();
		if ( ++i == UDP_SERVER_TX_DELAY / UDP_SERVER_RX_DELAY ) {
			i = 0;
			/* every 5 sec, in the reality...)) */
			__welcome();
		}
	}
	udp_ev3_close();
	closelog();
	return ( 0 );
}

// CLIENT ////////////////////////////////////////
#else

static int __wait_reply( void )
{
	int i;

	for ( i = 0; i < UDP_CLIENT_RX_TRIES; i++ ) {
		Sleep( UDP_CLIENT_RX_WAIT );

		switch ( __receive()) {
		case EOF:
			/* ERROR */
			return ( 0 );

		case EV3_KEYS:
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
	for ( i = 0; i < UDP_CLIENT_TX_TRIES; i++ ) {
		__transmit( t->fn_size + t->data_size );
		if ( __wait_reply()) {
			return ( __r_msg.head.data_size );
		}
	}
	return ( 0 );
}

int udp_ev3_multi_write( uint8_t *sn, uint16_t pos, char *fn, void *data, int sz )
{
	PEV3_MESSAGE_HEADER t = &__t_msg.head;
	PEV3_MULTI_WRITE_SUBHEADER sub = ( void *) __t_msg.body;
	char *p = ( char *) __t_msg.body + sizeof( EV3_MULTI_WRITE_SUBHEADER );
	int i;

	t->type = EV3_MULTI_WRITE;
	t->id = ++__t_last;
	t->fn_size = strlen( fn ) + 1;
	t->data_size = sz;
	for ( i = 0; i < DESC_VEC_LEN; i++ ) {
		if ( *sn < DESC_LIMIT ) {
			sub->sn[ i ] = *sn;
			sn++;
		} else {
			sub->sn[ i ] = DESC_LIMIT;
		}
	}
	sub->pos = pos;
	memcpy( p, fn, t->fn_size );
	memcpy( p + t->fn_size, data, t->data_size );
	for ( i = 0; i < UDP_CLIENT_TX_TRIES; i++ ) {
		__transmit( sizeof( EV3_MULTI_WRITE_SUBHEADER ) + t->fn_size + t->data_size );
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
	for ( i = 0; i < UDP_CLIENT_TX_TRIES; i++ ) {
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

int udp_ev3_read_keys( uint8_t *buf )
{
	return __udp_ev3_read( EV3_READ_KEYS, "", buf, sizeof( uint8_t ));

}

int udp_ev3_listdir( char *fn, void *buf, int sz )
{
	return __udp_ev3_read( EV3_LIST_DIR, fn, buf, sz );
}

int udp_ev3_catch_address( void )
{
	if ( __receive() == EV3_WELCOME ) {
		__t_addr.sin_addr.s_addr = __r_addr.sin_addr.s_addr;
		return ( 1 );
	}
	return ( 0 );
}

int udp_ev3_poweroff( void )
{
	PEV3_MESSAGE_HEADER h = &__t_msg.head;
	int i;

	h->type = EV3_POWEROFF;
	h->id = ++__t_last;
	h->fn_size = 0x5555;
	h->data_size = 0xAAAA;
	for ( i = 0; i < UDP_CLIENT_TX_TRIES; i++ ) {
		__transmit( 0 );
		if ( __wait_reply()) {
			return ( 1 );
		}
	}
	return ( 0 );
}

//////////////////////////////////////////////////
#endif

/** \} */
