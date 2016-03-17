/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  port.c
 *  \brief  ev3dev-c Ports example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

int main( void )
{
	char s[ 256 ];
	int i;
	uint8_t sn;

	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );
	ev3_port_init();

	printf( "Found ports:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_port[ i ].type_inx != PORT_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_port_type( ev3_port[ i ].type_inx ));
			printf( "  port = %s\n", ev3_port_port_name( i, s ));
			if ( get_port_mode( i, s, sizeof( s ))) {
				printf( "  mode = %s\n", s );
			}
		}
	}
	sn = ev3_search_port( INPUT_2, EXT_PORT__NONE_ );
	printf( "Port '%s'\n", ev3_port_name( INPUT_2, EXT_PORT__NONE_, 0, s ));
	if ( get_port_modes( sn, s, sizeof( s ))) {
		printf( "Modes: %s\n", s );
	} else {
		printf( "ERROR: get_port_modes()\n" );
	}
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
