/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  ev3_pool.c
 *  \brief  ev3dev-c example of wrapping of the library functions.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <string.h>
#include "ev3_pool.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( ms ) usleep(( ms ) * 1000 )

//////////////////////////////////////////////////
#endif

static uint8_t output_to_pool( uint8_t port )
{
	switch ( port ) {
	case OUTPUT_A:
		return ( OUTA );
	case OUTPUT_B:
		return ( OUTB );
	case OUTPUT_C:
		return ( OUTC );
	case OUTPUT_D:
		return ( OUTD );
	}
	return ( 0 );
}

static uint8_t input_to_pool( uint8_t port )
{
	switch ( port ) {
	case INPUT_1:
		return ( IN1 );
	case INPUT_2:
		return ( IN2 );
	case INPUT_3:
		return ( IN3 );
	case INPUT_4:
		return ( IN4 );
	}
	return ( 0 );
}

static uint8_t out_to_output( uint8_t out )
{
	switch ( out ) {
	case OUTA:
		return ( OUTPUT_A );
	case OUTB:
		return ( OUTPUT_B );
	case OUTC:
		return ( OUTPUT_C );
	case OUTD:
		return ( OUTPUT_D );
	}
	return ( EV3_PORT__NONE_ );
}

static uint8_t in_to_input( uint8_t in )
{
	switch ( in ) {
	case IN1:
		return ( INPUT_1 );
	case IN2:
		return ( INPUT_2 );
	case IN3:
		return ( INPUT_3 );
	case IN4:
		return ( INPUT_4 );
	}
	return ( EV3_PORT__NONE_ );
}

static bool tacho_pool_to_desc( uint8_t pool, uint8_t *sn )
{
	uint8_t _sn;

	memset( sn, DESC_VEC_LEN, OUT_COUNT );
	for ( _sn = 0; _sn < DESC_LIMIT; _sn++ ) {
		if ( ev3_tacho[ _sn ].type_inx != TACHO_TYPE__NONE_ ) {
			uint8_t out = output_to_pool( ev3_tacho[ _sn ].port );
			if ( out & pool ) {
				*sn = _sn;
				++sn;
				pool &= ~out;
				if ( pool == 0 ) return ( true );
			}
		}
	}
	return ( false );
}

static bool sensor_pool_to_desc( uint8_t pool, uint8_t *sn )
{
	uint8_t _sn;

	memset( sn, DESC_VEC_LEN, OUT_COUNT );
	for ( _sn = 0; _sn < DESC_LIMIT; _sn++ ) {
		if ( ev3_sensor[ _sn ].type_inx != SENSOR_TYPE__NONE_ ) {
			uint8_t in = input_to_pool( ev3_sensor[ _sn ].port );
			if ( in & pool ) {
				*sn = _sn;
				++sn;
				pool &= ~in;
				if ( pool == 0 ) return ( true );
			}
		}
	}
	return ( false );
}

bool tacho_is_plugged( uint8_t pool )
{
	uint8_t sn;
	uint8_t i;

	if ( pool == 0 ) return ( false );

	for ( i = 0; i < OUT_COUNT; i++ ) {
		uint8_t out = ( 1 << i );
		if (( out & pool ) && ( !ev3_search_tacho_plugged_in( out_to_output( out ), EXT_PORT__NONE_, &sn, 0 ))) {
			return ( false );
		}
	}
	return ( true );
}

bool tacho_is_running( uint8_t pool )
{
	uint8_t sn;
	uint8_t i;
	FLAGS_T state = TACHO_STATE__NONE_;

	for ( i = 0; i < OUT_COUNT; i++ ) {
		uint8_t out = ( 1 << i );
		if (( out & pool ) && ( ev3_search_tacho_plugged_in( out_to_output( out ), EXT_PORT__NONE_, &sn, 0 ))) {
			get_tacho_state_flags( sn, &state );
			if ( state != TACHO_STATE__NONE_ ) return ( true );
		}
	}
	return ( false );
}

bool tacho_command( uint8_t pool, int command )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_command_inx( sn, command ));
	}
	return ( false );
}

bool tacho_reset( uint8_t pool )
{
	return ( tacho_command( pool, TACHO_RESET ));
}

bool tacho_run_forever( uint8_t pool )
{
	return ( tacho_command( pool, TACHO_RUN_FOREVER ));
}

bool tacho_run_to_rel_pos( uint8_t pool )
{
	return ( tacho_command( pool, TACHO_RUN_TO_REL_POS ));
}

bool tacho_run_timed( uint8_t pool )
{
	return ( tacho_command( pool, TACHO_RUN_TIMED ));
}

bool tacho_stop( uint8_t pool )
{
	return ( tacho_command( pool, TACHO_STOP ));
}

int tacho_get_max_speed( uint8_t out )
{
	uint8_t sn;
	int val = 0;  /* default result */

	if ( out == 0 ) return ( val );

	if ( ev3_search_tacho_plugged_in( out_to_output( out ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_max_speed( sn, &val );
	}
	return ( val );
}

bool tacho_set_speed( uint8_t pool, int speed )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_speed_sp( sn, speed ));
	}
	return ( false );
}

bool tacho_set_duty_cycle( uint8_t pool, int rate )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_duty_cycle_sp( sn, rate ));
	}
	return ( false );
}

bool tacho_set_position( uint8_t pool, int pos )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_position_sp( sn, pos ));
	}
	return ( false );
}

bool tacho_set_time( uint8_t pool, int ms )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_time_sp( sn, ms ));
	}
	return ( false );
}

bool sensor_is_plugged( uint8_t pool )
{
	uint8_t sn;
	uint8_t i;

	if ( pool == 0 ) return ( false );

	for ( i = 0; i < IN_COUNT; i++ ) {
		uint8_t in = ( 1 << i );
		if (( in & pool ) && ( !ev3_search_sensor_plugged_in( in_to_input( in ), EXT_PORT__NONE_, &sn, 0 ))) {
			return ( false );
		}
	}
	return ( true );
}

uint8_t sensor_search( INX_T type_inx )
{
	uint8_t sn;

	if ( ev3_search_sensor( type_inx, &sn, 0 )) {
		return ( input_to_pool( ev3_sensor[ sn ].port ));
	}
	return ( 0 );
}

int sensor_get_value( uint8_t in, uint8_t inx )
{
	uint8_t sn;
	int val = 0;  /* default result */

	if ( in == 0 ) return ( val );

	if ( ev3_search_sensor_plugged_in( in_to_input( in ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value( inx, sn, &val );
	}
	return ( val );
}

bool sensor_set_mode( uint8_t pool, int mode )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( sensor_pool_to_desc( pool, sn )) {
		return ( multi_set_sensor_mode_inx( sn, mode ));
	}
	return ( false );
}

bool ir_set_mode_remote( uint8_t pool )
{
	return ( sensor_set_mode( pool, LEGO_EV3_IR_IR_REMOTE ));
}

bool ir_set_mode_prox( uint8_t pool )
{
	return ( sensor_set_mode( pool, LEGO_EV3_IR_IR_PROX ));
}

bool brick_init( void )
{
	if ( ev3_init() < 1 ) return ( false );
	ev3_sensor_init();
	ev3_tacho_init();
	return ( true );
}

void brick_uninit( void )
{
	ev3_uninit();
}

int brick_keys( void )
{
	uint8_t keys = 0;  /* default result */

	ev3_read_keys( &keys );
	return ( keys );
}

void sleep_ms( uint32_t ms )
{
	Sleep( ms );
}
