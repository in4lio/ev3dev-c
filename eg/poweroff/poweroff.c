/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  poweroff.c
 *  \brief  ev3dev-c Poweroff example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "ev3.h"

/*  WARNING!
 *  Please build and install ev3dev-c static library before make this example.
 *  See README.
 */

int main( void )
{
	char s[ 256 ];
	char *p;

	if ( ev3_init() < 1 ) return ( 1 );

	printf( "Enter 'bye' to power-off the EV3 brick: " );
	scanf( "%4s", s );
	for ( p = s; *p; p++ ) *p = tolower( *p );

	if ( strcmp( s, "bye" ) == 0 ) {
		ev3_poweroff();
		printf( "Goodbye!\n" );
	} else {
		printf( "Misspelling.\n" );
	}
	ev3_uninit();

	return ( 0 );
}
