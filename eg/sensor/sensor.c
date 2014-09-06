/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  sensor.c
 *  \brief  ev3dev-c sensors example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  The MIT License
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "modp_numtoa.h"
#include "ev3.h"
#include "ev3_sensor.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>
#include <conio.h>

#define CHAR_ENTER  '\x0D'

/* Non-blocking console input */
static int __getch( void )
{
	return ( kbhit() ? _getch() : EOF );
}

static void getch_init( void )
{
}

static void getch_uninit( void )
{
}

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#include <termios.h>

#define Sleep( msec ) usleep(( msec ) * 1000 )

#define CHAR_ENTER  '\x0A'

/* Non-blocking console input */
static int __getch( void )
{
	return fgetc( stdin );
}

static struct termios getch_o_attr;

static void getch_init( void )
{
	struct termios n_attr;

	/* Set terminal to raw mode */
	tcgetattr( fileno( stdin ), &getch_o_attr );
	memcpy( &n_attr, &getch_o_attr, sizeof( struct termios ));
	n_attr.c_lflag &= ~( ECHO | ICANON );
	n_attr.c_cc[ VTIME ] = 0;
	n_attr.c_cc[ VMIN  ] = 0;
	tcsetattr( fileno( stdin ), TCSANOW, &n_attr );
}

static void getch_uninit( void )
{
	/* Restore original terminal attributes */
	tcsetattr( fileno( stdin ), TCSANOW, &getch_o_attr );
}

//////////////////////////////////////////////////
#endif

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

static bool __pressed( int port )
{
	int val;

	if ( port == EOF ) return ( __getch() == CHAR_ENTER );

	return ( get_sensor_value( 0, ev3_sensor[ port ].id, &val ) && ( val != 0 ));
}

int main( void )
{
	char s[ 255 ];
	char *pch;
	int p_color, p_touch;
	int val;
	uint32_t n, i, ii;

	printf( "Waiting the EV3 brick online...\n" );
	ev3_init();
	printf( "*** ( EV3 ) Hello! ***\n" );
	ev3_sensor_init();
	getch_init();

	printf( "Found sensors:\n" );
	for ( i = 0; i < INPUT__COUNT_; i++ ) {
		if ( ev3_sensor[ i ].connected ) {
			uint8_t id = ev3_sensor[ i ].id;

			printf( "  port = in%d\n", i + 1 );
			pch = ev3_sensor_type( ev3_sensor[ i ].type_id );
			if ( pch ) {
				printf( "  type = %s\n", pch );
			} else {
				printf( "  type_id = %d\n", ev3_sensor[ i ].type_id );
			}
			if ( get_sensor_mode( id, s, sizeof( s ))) {
				printf( "  mode = %s\n", s );
			}
			if ( get_sensor_num_values( id, &n )) {
				for ( ii = 0; ii < n; ii++ ) {
					if ( get_sensor_value( ii, id, &val )) {
						printf( "  value%d = %d\n", ii, val );
					}
				}
			}
		}
	}
	p_touch = ev3_sensor_port( EV3_TOUCH );
	if ( p_touch != EOF ) {
		printf( "EV3_TOUCH is found, press BUTTON for EXIT...\n" );
	} else {
		printf( "EV3_TOUCH is not found, press ENTER for EXIT...\n" );
	}
	p_color = ev3_sensor_port( EV3_COLOR );
	if ( p_color != EOF ) {
		uint8_t id = ev3_sensor[ p_color ].id;

		printf( "EV3_COLOR is found, reading COLOR...\n" );
		set_sensor_mode( id, "COL-COLOR" );
		for ( ; ; ) {
			if ( !get_sensor_value( 0, id, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
				val = 0;
			}
			printf( "\r(%s)", color[ val ]);
			fflush( stdout );
			if ( __pressed( p_touch )) break;
			Sleep( 200 );
			printf( "\r        " );
			fflush( stdout );
			if ( __pressed( p_touch )) break;
			Sleep( 200 );
		}
	} else {
		printf( "EV3_COLOR is not found\n" );
		while ( !__pressed( p_touch )) Sleep( 100 );
	}
	getch_uninit();
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
