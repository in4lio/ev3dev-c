/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  remote.c
 *  \brief  ev3dev-c example of "brick" simplified library.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "coroutine.h"
#include "brick.h"

#define SPEED_LINEAR    75  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR  50  /* ... for circular motion */

int max_speed;         /* Motor maximal speed (will be detected) */

#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )

#define IR_CHANNEL     0

POOL_T ir;             /* IR sensor port (will be detected) */

enum {
	STOP,
	FORTH,
	BACK,
	LEFT,
	RIGHT,
};
int command = STOP;    /* Command for `drive` coroutine */

int alive;             /* Program is alive */

int init( void )
{
	if ( tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )) {  /* any type of motor */
		max_speed = tacho_get_max_speed( MOTOR_LEFT, 0 );
		tacho_reset( MOTOR_BOTH );
	} else {
		printf( "Please, plug LEFT motor in C port,\n"
		"RIGHT motor in B port and try again.\n"
		);
		/* Inoperative without motors */
		return ( 0 );
	}

	ir = sensor_search( LEGO_EV3_IR );
	if ( ir ) {
		ir_set_mode_ir_remote( ir );

		printf(	"IR remote control:\n"
		"RED UP   & BLUE UP   - forward\n"
		"RED DOWN & BLUE DOWN - backward\n"
		"RED UP   | BLUE DOWN - left\n"
		"RED DOWN | BLUE UP   - right\n"
		);
	} else {
		printf( "IR sensor is NOT found.\n"
		"Please, use the EV3 brick buttons.\n"
		);
	}
	printf( "Press BACK on the EV3 brick for EXIT...\n" );

	return ( 1 );
}

CORO_CONTEXT( handle_ir_control );
CORO_CONTEXT( handle_brick_control );
CORO_CONTEXT( drive );

/* Coroutine of IR remote control handling */
CORO_DEFINE( handle_ir_control )
{
	CORO_LOCAL int btns, pressed = IR_REMOTE__NONE_;

	CORO_BEGIN();
	if ( ir == SOCKET__NONE_ ) CORO_QUIT();

	for ( ; ; ) {
		/* Waiting any IR RC button is pressed or released */
		CORO_WAIT(( btns = sensor_get_value( IR_CHANNEL, ir, IR_REMOTE__NONE_ )) != pressed );
		pressed = btns;

		switch ( pressed ) {
		/* Forward */
		case RED_UP_BLUE_UP:
			command = FORTH;
			break;
		/* Backward */
		case RED_DOWN_BLUE_DOWN:
			command = BACK;
			break;
		/* Left */
		case RED_UP:
		case RED_UP_BLUE_DOWN:
		case BLUE_DOWN:
			command = LEFT;
			break;
		/* Right */
		case BLUE_UP:
		case RED_DOWN_BLUE_UP:
		case RED_DOWN:
			command = RIGHT;
			break;
		/* Stop */
		case IR_REMOTE__NONE_:
		case RED_UP_RED_DOWN:
		case BLUE_UP_BLUE_DOWN:
		case BEACON_MODE_ON:
			command = STOP;
			break;
		}
		CORO_YIELD();
	}
	CORO_END();
}

/* Coroutine of the EV3 brick keys handling */
CORO_DEFINE( handle_brick_control )
{
	CORO_LOCAL uint8_t keys, pressed = EV3_KEY__NONE_;

	CORO_BEGIN();
	for ( ; ; ) {
		/* Waiting any brick's key is pressed or released */
		CORO_WAIT(( keys = brick_keys()) != pressed );
		pressed = keys;

		switch ( pressed ) {
		/* Quit */
		case EV3_KEY_BACK:
			command = STOP;
			alive = 0;
			break;
		/* Stop */
		case EV3_KEY__NONE_:
		case EV3_KEY_CENTER:
			command = STOP;
			break;
		/* Forward */
		case EV3_KEY_UP:
			command = FORTH;
 			break;
		/* Backward */
		case EV3_KEY_DOWN:
			command = BACK;
			break;
		/* Left */
		case EV3_KEY_LEFT:
			command = LEFT;
			break;
		/* Right */
		case EV3_KEY_RIGHT:
			command = RIGHT;
			break;
		}
		CORO_YIELD();
	}
	CORO_END();
}

/* Coroutine of control the motors */
CORO_DEFINE( drive )
{
	CORO_LOCAL int speed_linear, speed_circular;
	CORO_LOCAL int state = STOP;

	CORO_BEGIN();
	speed_linear = max_speed * SPEED_LINEAR / 100;
	speed_circular = max_speed * SPEED_CIRCULAR / 100;

	for ( ; ; ) {
		/* Waiting new command */
		CORO_WAIT( state != command );

		switch ( command ) {

		case STOP:
			tacho_stop( MOTOR_BOTH );
			/* Waiting the vehicle is stopped */
			CORO_WAIT( !tacho_is_running( MOTOR_BOTH ));
			break;

		case FORTH:
			tacho_set_speed_sp( MOTOR_BOTH, -speed_linear );
			tacho_run_forever( MOTOR_BOTH );
			break;

		case BACK:
			tacho_set_speed_sp( MOTOR_BOTH, speed_linear );
			tacho_run_forever( MOTOR_BOTH );
			break;

		case LEFT:
			tacho_set_speed_sp( MOTOR_LEFT, speed_circular );
			tacho_set_speed_sp( MOTOR_RIGHT, -speed_circular );
			tacho_run_forever( MOTOR_BOTH );
			break;

		case RIGHT:
			tacho_set_speed_sp( MOTOR_LEFT, -speed_circular );
			tacho_set_speed_sp( MOTOR_RIGHT, speed_circular );
			tacho_run_forever( MOTOR_BOTH );
			break;
		}
		state = command;
	}
	CORO_END();
}

int main( void )
{
	printf( "Waiting the EV3 brick online...\n" );
	if ( !brick_init()) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );
	alive = init();

	while ( alive ) {
		CORO_CALL( handle_ir_control );
		CORO_CALL( handle_brick_control );
		CORO_CALL( drive );
		sleep_ms( 10 );
	}
	brick_uninit();

	printf( "*** ( EV3 ) Bye! ***\n" );
	return ( 0 );
}
