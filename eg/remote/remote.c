/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  remote.c
 *  \brief  ev3dev-c example of wrapping of the library functions.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include <ev3_pool.h>

#define SPEED_LINEAR    75  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR  50  /* ... for circular motion */

int max_speed;         /* Motor maximal speed */

#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )

#define IR_CHANNEL     0

uint8_t ir;            /* Port will be detected */

enum {
	STOP,
	FORTH,
	BACK,
	LEFT,
	RIGHT,
};

int state;             /* Current state */
int command;           /* Command for 'drive' coroutine */

int alive;             /* Program is alive */

int init( void )
{
	if ( tacho_is_plugged( MOTOR_BOTH )) {
		max_speed = tacho_get_max_speed( MOTOR_LEFT );
		tacho_reset( MOTOR_BOTH );
	} else {
		printf( "Please, plug LEFT motor in C port,\n"
		"RIGHT motor in B port and try again.\n"
		);
		return ( 0 );  /* Inoperative without both motors */
	}
	command	= state = STOP;

	ir = sensor_search( LEGO_EV3_IR );
	if ( ir ) {
		ir_set_mode_remote( ir );

		printf(	"IR remote control:\n"
		"RED UP & BLUE UP     - forward\n"
		"RED DOWN & BLUE DOWN - backward\n"
		"RED UP | BLUE DOWN   - left\n"
		"RED DOWN | BLUE UP   - right\n"
		);
	} else {
		printf( "IR sensor is NOT found,\n"
		"use the EV3 brick buttons.\n"
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
	CORO_LOCAL int pressed = IR_REMOTE__NONE_;

	CORO_BEGIN();
	if ( ir == 0 ) CORO_QUIT();

	for ( ; ; ) {
		/* Waiting any button is pressed or released */
		CORO_WAIT(( sensor_get_value( ir, IR_CHANNEL ) != pressed ), );

		/* Get state of IR RC buttons */
		pressed = sensor_get_value( ir, IR_CHANNEL );
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
		/* Waiting any key is pressed or released */
		CORO_WAIT( ev3_read_keys( &keys ) && ( keys != pressed ), );
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

	CORO_BEGIN();
	speed_linear = max_speed * SPEED_LINEAR / 100;
	speed_circular = max_speed * SPEED_CIRCULAR / 100;

	for ( ; ; ) {
		/* Waiting new command */
		CORO_WAIT( state != command, );

		switch ( command ) {

		case STOP:
			tacho_stop( MOTOR_BOTH );
			/* Waiting the vehicle is stopped */
			CORO_WAIT( !tacho_is_running( MOTOR_BOTH ), );
			break;

		case FORTH:
			tacho_set_speed( MOTOR_BOTH, -speed_linear );
			tacho_run_forever( MOTOR_BOTH );
			break;

		case BACK:
			tacho_set_speed( MOTOR_BOTH, speed_linear );
			tacho_run_forever( MOTOR_BOTH );
			break;

		case LEFT:
			tacho_set_speed( MOTOR_LEFT, speed_circular );
			tacho_set_speed( MOTOR_RIGHT, -speed_circular );
			tacho_run_forever( MOTOR_BOTH );
			break;

		case RIGHT:
			tacho_set_speed( MOTOR_LEFT, -speed_circular );
			tacho_set_speed( MOTOR_RIGHT, speed_circular );
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
