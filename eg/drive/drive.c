/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  drive.c
 *  \brief  ev3dev-c example of using coroutines to control the motors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "coroutine.h"
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
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

#define L_MOTOR_PORT      OUTPUT_C
#define L_MOTOR_EXT_PORT  EXT_PORT__NONE_
#define R_MOTOR_PORT      OUTPUT_B
#define R_MOTOR_EXT_PORT  EXT_PORT__NONE_
#define IR_CHANNEL        0

#define SPEED_LINEAR      75  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR    50  /* ... for circular motion */

int max_speed;  /* Motor maximal speed */

#define DEGREE_TO_COUNT( d )  (( d ) * 260 / 90 )

int app_alive;

enum {
	MODE_REMOTE,  /* IR remote control */
	MODE_AUTO,    /* Self-driving */
};

int mode;  /* Driving mode */

enum {
	MOVE_NONE,
	MOVE_FORWARD,
	MOVE_BACKWARD,
	TURN_LEFT,
	TURN_RIGHT,
	TURN_ANGLE,
	STEP_BACKWARD,
};

int moving;   /* Current moving */
int command;  /* Command for the 'drive' coroutine */
int angle;    /* Angle of rotation */

uint8_t ir, touch;  /* Sequence numbers of sensors */
enum { L, R };
uint8_t motor[ 3 ] = { DESC_LIMIT, DESC_LIMIT, DESC_LIMIT };  /* Sequence numbers of motors */

static void _set_mode( int value )
{
	if ( value == MODE_AUTO ) {
		/* IR measuring of distance */
		set_sensor_mode_inx( ir, LEGO_EV3_IR_IR_PROX );
		mode = MODE_AUTO;
	} else {
		/* IR remote control */
		set_sensor_mode_inx( ir, LEGO_EV3_IR_IR_REMOTE );
		mode = MODE_REMOTE;
	}
}

static void _run_forever( int l_speed, int r_speed )
{
	set_tacho_speed_sp( motor[ L ], l_speed );
	set_tacho_speed_sp( motor[ R ], r_speed );
	multi_set_tacho_command_inx( motor, TACHO_RUN_FOREVER );
}

static void _run_to_rel_pos( int l_speed, int l_pos, int r_speed, int r_pos )
{
	set_tacho_speed_sp( motor[ L ], l_speed );
	set_tacho_speed_sp( motor[ R ], r_speed );
	set_tacho_position_sp( motor[ L ], l_pos );
	set_tacho_position_sp( motor[ R ], r_pos );
	multi_set_tacho_command_inx( motor, TACHO_RUN_TO_REL_POS );
}

static void _run_timed( int l_speed, int r_speed, int ms )
{
	set_tacho_speed_sp( motor[ L ], l_speed );
	set_tacho_speed_sp( motor[ R ], r_speed );
	multi_set_tacho_time_sp( motor, ms );
	multi_set_tacho_command_inx( motor, TACHO_RUN_TIMED );
}

static int _is_running( void )
{
	FLAGS_T state = TACHO_STATE__NONE_;

	get_tacho_state_flags( motor[ L ], &state );
	if ( state != TACHO_STATE__NONE_ ) return ( 1 );
	get_tacho_state_flags( motor[ R ], &state );
	if ( state != TACHO_STATE__NONE_ ) return ( 1 );

	return ( 0 );
}

static void _stop( void )
{
	multi_set_tacho_command_inx( motor, TACHO_STOP );
}

int app_init( void )
{
	char s[ 16 ];

	if ( ev3_search_tacho_plugged_in( L_MOTOR_PORT, L_MOTOR_EXT_PORT, motor + L, 0 )) {
		get_tacho_max_speed( motor[ L ], &max_speed );
		/* Reset the motor */
		set_tacho_command_inx( motor[ L ], TACHO_RESET );
	} else {
		printf( "LEFT motor (%s) is NOT found.\n", ev3_port_name( L_MOTOR_PORT, L_MOTOR_EXT_PORT, 0, s ));
		/* Inoperative without left motor */
		return ( 0 );
	}
	if ( ev3_search_tacho_plugged_in( R_MOTOR_PORT, R_MOTOR_EXT_PORT, motor + R, 0 )) {
		/* Reset the motor */
		set_tacho_command_inx( motor[ R ], TACHO_RESET );
	} else {
		printf( "RIGHT motor (%s) is NOT found.\n", ev3_port_name( R_MOTOR_PORT, R_MOTOR_EXT_PORT, 0, s ));
		/* Inoperative without right motor */
		return ( 0 );
	}
	command	= moving = MOVE_NONE;

	if ( ev3_search_sensor( LEGO_EV3_IR, &ir, 0 )) {
		_set_mode( MODE_REMOTE );
	} else {
		printf( "IR sensor is NOT found.\n" );
		/* Inoperative without IR sensor */
		return ( 0 );
	}
	printf(	"IR remote control:\n"
	"RED UP & BLUE UP     - forward\n"
	"RED DOWN & BLUE DOWN - backward\n"
	"RED UP | BLUE DOWN   - left\n"
	"RED DOWN | BLUE UP   - right\n"
	"To switch between IR remote control and\n"
	"self-driving" );
	if ( ev3_search_sensor( LEGO_EV3_TOUCH, &touch, 0 )) {
		printf( " use the TOUCH sensor.\n" );
	} else {
		touch = DESC_LIMIT;
		printf( " press UP on the EV3 brick.\n" );
	}
	printf( "Press BACK on the EV3 brick for EXIT...\n" );
	return ( 1 );
}

CORO_CONTEXT( handle_touch );
CORO_CONTEXT( handle_brick_control );
CORO_CONTEXT( handle_ir_control );
CORO_CONTEXT( handle_ir_proximity );
CORO_CONTEXT( drive );

/* Coroutine of the TOUCH sensor handling */
CORO_DEFINE( handle_touch )
{
	CORO_LOCAL int val;

	CORO_BEGIN();
	if ( touch == DESC_LIMIT ) CORO_QUIT();

	for ( ; ; ) {
		/* Waiting the button is pressed */
		CORO_WAIT( get_sensor_value( 0, touch, &val ) && ( val ));
		/* Stop the vehicle */
		command = MOVE_NONE;
		/* Switch mode */
		_set_mode(( mode == MODE_REMOTE ) ? MODE_AUTO : MODE_REMOTE );
		/* Waiting the button is released */
		CORO_WAIT( get_sensor_value( 0, touch, &val ) && ( !val ));
	}
	CORO_END();
}

/* Coroutine of the EV3 brick keys handling */
CORO_DEFINE( handle_brick_control )
{
	CORO_LOCAL uint8_t keys, pressed = EV3_KEY__NONE_;

	CORO_BEGIN();
	for ( ; ; ) {
		/* Waiting any key is pressed or released */
		CORO_WAIT( ev3_read_keys( &keys ) && ( keys != pressed ));
		pressed = keys;

		if ( pressed & EV3_KEY_BACK ) {
			/* Stop the vehicle */
			command = MOVE_NONE;
			/* Quit */
			app_alive = 0;

		} else if ( pressed & EV3_KEY_UP ) {
			/* Stop the vehicle */
			command = MOVE_NONE;
			/* Switch mode */
			_set_mode(( mode == MODE_REMOTE ) ? MODE_AUTO : MODE_REMOTE );
		}
		CORO_YIELD();
	}
	CORO_END();
}

/* Coroutine of IR remote control handling */
CORO_DEFINE( handle_ir_control )
{
	CORO_LOCAL int val;

	CORO_BEGIN();
	for ( ; ; ) {
		/* Waiting IR remote control mode */
		CORO_WAIT( mode == MODE_REMOTE );

		val = IR_REMOTE__NONE_;
		get_sensor_value( IR_CHANNEL, ir, &val );

		switch ( val ) {
		/* Forward */
		case RED_UP_BLUE_UP:
			command = MOVE_FORWARD;
			break;
		/* Backward */
		case RED_DOWN_BLUE_DOWN:
			command = MOVE_BACKWARD;
			break;
		/* Left */
		case RED_UP:
		case RED_UP_BLUE_DOWN:
		case BLUE_DOWN:
			command = TURN_LEFT;
			break;
		/* Right */
		case BLUE_UP:
		case RED_DOWN_BLUE_UP:
		case RED_DOWN:
			command = TURN_RIGHT;
			break;
		/* Stop */
		case IR_REMOTE__NONE_:
		case RED_UP_RED_DOWN:
		case BLUE_UP_BLUE_DOWN:
		case BEACON_MODE_ON:
			command = MOVE_NONE;
			break;
		}
		CORO_YIELD();
	}
	CORO_END();
}

/* Coroutine of IR proximity handling (self-driving),
   based on Franz Detro drive_test.cpp */
CORO_DEFINE( handle_ir_proximity )
{
	CORO_LOCAL int front, prox;

	CORO_BEGIN();
	for ( ; ; ) {
		/* Waiting self-driving mode */
		CORO_WAIT( mode == MODE_AUTO );

		prox = 0;
		get_sensor_value( 0, ir, &prox );
		if ( prox == 0 ) {
			/* Oops! Stop the vehicle */
			command = MOVE_NONE;

		} else if ( prox < 20 ) {  /* Need for detour... */
			front = prox;
			/* Look to the left */
			angle = -30;
			do {
				command = TURN_ANGLE;
				CORO_WAIT( command == MOVE_NONE );

				prox = 0;
				get_sensor_value( 0, ir, &prox );
				if ( prox < front ) {
					if ( angle < 0 ) {
						/* Still looking to the left - look to the right */
						angle = 60;
					} else {
						/* Step back */
						command = STEP_BACKWARD;
						CORO_WAIT( command == MOVE_NONE );
					}
				}
			} while (( prox > 0 ) && ( prox < 40 ) && ( mode == MODE_AUTO ));

		} else {
			/* Track is clear - Go! */
			command = MOVE_FORWARD;
		}
		CORO_YIELD();
	}
	CORO_END();
}

/* Coroutine of control the motors */
CORO_DEFINE( drive )
{
	CORO_LOCAL int speed_linear, speed_circular;
	CORO_LOCAL int _wait_stopped;

	CORO_BEGIN();
	speed_linear = max_speed * SPEED_LINEAR / 100;
	speed_circular = max_speed * SPEED_CIRCULAR / 100;

	for ( ; ; ) {
		/* Waiting new command */
		CORO_WAIT( moving != command );

		_wait_stopped = 0;
		switch ( command ) {

		case MOVE_NONE:
			_stop();
			_wait_stopped = 1;
			break;

		case MOVE_FORWARD:
			_run_forever( -speed_linear, -speed_linear );
			break;

		case MOVE_BACKWARD:
			_run_forever( speed_linear, speed_linear );
			break;

		case TURN_LEFT:
			_run_forever( speed_circular, -speed_circular );
			break;

		case TURN_RIGHT:
			_run_forever( -speed_circular, speed_circular );
			break;

		case TURN_ANGLE:
			_run_to_rel_pos( speed_circular, DEGREE_TO_COUNT( -angle )
			, speed_circular, DEGREE_TO_COUNT( angle ));
			_wait_stopped = 1;
			break;

		case STEP_BACKWARD:
			_run_timed( speed_linear, speed_linear, 1000 );
			_wait_stopped = 1;
			break;
		}
		moving = command;

		if ( _wait_stopped ) {
			/* Waiting the command is completed */
			CORO_WAIT( !_is_running());

			command = moving = MOVE_NONE;
		}
	}
	CORO_END();
}

int main( void )
{
	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );
	ev3_sensor_init();
	ev3_tacho_init();

	app_alive = app_init();
	while ( app_alive ) {
		CORO_CALL( handle_ir_control );
		CORO_CALL( handle_ir_proximity );
		CORO_CALL( handle_touch );
		CORO_CALL( handle_brick_control );
		CORO_CALL( drive );
		Sleep( 10 );
	}
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
