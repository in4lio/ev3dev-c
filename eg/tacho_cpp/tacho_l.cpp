/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  tacho.cpp
 *  \brief  ev3dev-c Tacho Motors example in C++.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <iostream>
#include "ev3.h"
#include "ev3_tacho.h"

using namespace std;

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
	uint8_t sn;

	cout << "Waiting the EV3 brick online..." << endl;
	if ( ev3_init() < 1 ) return ( 1 );

	ev3_tacho_init();

	cout << "*** ( EV3 ) Hello! ***" << endl;

	if ( ev3_search_tacho( LEGO_EV3_L_MOTOR, &sn, 0 )) {

		cout << "LEGO_EV3_L_MOTOR is found, run forever..." << endl;
		set_tacho_stop_action_inx( sn, TACHO_COAST );
		set_tacho_speed_sp( sn, 800 );
		set_tacho_ramp_up_sp( sn, 500 );
		set_tacho_ramp_down_sp( sn, 500 );

		set_tacho_command_inx( sn, TACHO_RUN_FOREVER );
		cout << "wait 5 sec..." << endl;
		Sleep( 5000 );
		set_tacho_command_inx( sn, TACHO_STOP );
		Sleep( 500 );
		cout << "run to relative position..." << endl;
		set_tacho_position_sp( sn, 90 );
		set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
		Sleep( 500 );
		cout << "again..." << endl;
		set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
		Sleep( 500 );
		cout << "reversed run..." << endl;
		set_tacho_position_sp( sn, -90 );
		set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
		Sleep( 500 );
		cout << "again..." << endl;
		set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
		Sleep( 500 );
	} else {
		cout << "LEGO_EV3_L_MOTOR is NOT found." << endl;
	}
	ev3_uninit();
	cout << "*** ( EV3 ) Bye! ***" << endl;

	return ( 0 );
}
