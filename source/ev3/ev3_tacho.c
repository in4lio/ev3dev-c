
/*  ev3_tacho.c was generated by yup.py (yupp) 0.8b7
    out of ev3_tacho.yu-c at 2015-07-22 12:17
 *//**
 *  \file  ev3_tacho.c (ev3_tacho.yu-c)
 *  \brief  EV3 Tacho Motors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define EV3_TACHO_IMPLEMENT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "modp_numtoa.h"
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"

#define PATH_PREF_LEN  28
#define _ID_SPOT  "///"

#define PATH_COMMAND  "/sys/class/tacho-motor/motor" _ID_SPOT "command"
#define PATH_COMMANDS  "/sys/class/tacho-motor/motor" _ID_SPOT "commands"
#define PATH_COUNT_PER_ROT  "/sys/class/tacho-motor/motor" _ID_SPOT "count_per_rot"
#define PATH_DRIVER_NAME  "/sys/class/tacho-motor/motor" _ID_SPOT "driver_name"
#define PATH_DUTY_CYCLE  "/sys/class/tacho-motor/motor" _ID_SPOT "duty_cycle"
#define PATH_DUTY_CYCLE_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "duty_cycle_sp"
#define PATH_ENCODER_POLARITY  "/sys/class/tacho-motor/motor" _ID_SPOT "encoder_polarity"
#define PATH_HOLD_PID_KD  "/sys/class/tacho-motor/motor" _ID_SPOT "hold_pid/Kd"
#define PATH_HOLD_PID_KI  "/sys/class/tacho-motor/motor" _ID_SPOT "hold_pid/Ki"
#define PATH_HOLD_PID_KP  "/sys/class/tacho-motor/motor" _ID_SPOT "hold_pid/Kp"
#define PATH_POLARITY  "/sys/class/tacho-motor/motor" _ID_SPOT "polarity"
#define PATH_PORT_NAME  "/sys/class/tacho-motor/motor" _ID_SPOT "port_name"
#define PATH_POSITION  "/sys/class/tacho-motor/motor" _ID_SPOT "position"
#define PATH_POSITION_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "position_sp"
#define PATH_RAMP_DOWN_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "ramp_down_sp"
#define PATH_RAMP_UP_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "ramp_up_sp"
#define PATH_SPEED  "/sys/class/tacho-motor/motor" _ID_SPOT "speed"
#define PATH_SPEED_PID_KD  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_pid/Kd"
#define PATH_SPEED_PID_KI  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_pid/Ki"
#define PATH_SPEED_PID_KP  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_pid/Kp"
#define PATH_SPEED_REGULATION  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_regulation"
#define PATH_SPEED_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "speed_sp"
#define PATH_STATE  "/sys/class/tacho-motor/motor" _ID_SPOT "state"
#define PATH_STOP_COMMAND  "/sys/class/tacho-motor/motor" _ID_SPOT "stop_command"
#define PATH_STOP_COMMANDS  "/sys/class/tacho-motor/motor" _ID_SPOT "stop_commands"
#define PATH_TIME_SP  "/sys/class/tacho-motor/motor" _ID_SPOT "time_sp"

size_t set_tacho_command( uint8_t sn, char *value )
{
	char s[] = PATH_COMMAND;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_commands( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_COMMANDS;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_count_per_rot( uint8_t sn, int *buf )
{
	char s[] = PATH_COUNT_PER_ROT;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t get_tacho_driver_name( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_DRIVER_NAME;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_duty_cycle( uint8_t sn, int *buf )
{
	char s[] = PATH_DUTY_CYCLE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t get_tacho_duty_cycle_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_DUTY_CYCLE_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_duty_cycle_sp( uint8_t sn, int value )
{
	char s[] = PATH_DUTY_CYCLE_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_encoder_polarity( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_ENCODER_POLARITY;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_encoder_polarity( uint8_t sn, char *value )
{
	char s[] = PATH_ENCODER_POLARITY;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_hold_pid_Kd( uint8_t sn, int *buf )
{
	char s[] = PATH_HOLD_PID_KD;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_hold_pid_Kd( uint8_t sn, int value )
{
	char s[] = PATH_HOLD_PID_KD;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_hold_pid_Ki( uint8_t sn, int *buf )
{
	char s[] = PATH_HOLD_PID_KI;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_hold_pid_Ki( uint8_t sn, int value )
{
	char s[] = PATH_HOLD_PID_KI;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_hold_pid_Kp( uint8_t sn, int *buf )
{
	char s[] = PATH_HOLD_PID_KP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_hold_pid_Kp( uint8_t sn, int value )
{
	char s[] = PATH_HOLD_PID_KP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_polarity( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_POLARITY;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_polarity( uint8_t sn, char *value )
{
	char s[] = PATH_POLARITY;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_port_name( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_PORT_NAME;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_position( uint8_t sn, int *buf )
{
	char s[] = PATH_POSITION;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_position( uint8_t sn, int value )
{
	char s[] = PATH_POSITION;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_position_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_POSITION_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_position_sp( uint8_t sn, int value )
{
	char s[] = PATH_POSITION_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_ramp_down_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_RAMP_DOWN_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_ramp_down_sp( uint8_t sn, int value )
{
	char s[] = PATH_RAMP_DOWN_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_ramp_up_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_RAMP_UP_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_ramp_up_sp( uint8_t sn, int value )
{
	char s[] = PATH_RAMP_UP_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_speed( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t get_tacho_speed_pid_Kd( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_PID_KD;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_pid_Kd( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_PID_KD;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_speed_pid_Ki( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_PID_KI;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_pid_Ki( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_PID_KI;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_speed_pid_Kp( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_PID_KP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_pid_Kp( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_PID_KP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_speed_regulation( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_SPEED_REGULATION;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_speed_regulation( uint8_t sn, char *value )
{
	char s[] = PATH_SPEED_REGULATION;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_speed_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_SPEED_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_speed_sp( uint8_t sn, int value )
{
	char s[] = PATH_SPEED_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

size_t get_tacho_state( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_STATE;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_stop_command( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_STOP_COMMAND;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_tacho_stop_command( uint8_t sn, char *value )
{
	char s[] = PATH_STOP_COMMAND;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_tacho_stop_commands( uint8_t sn, char *buf, size_t sz )
{
	char s[] = PATH_STOP_COMMANDS;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_tacho_time_sp( uint8_t sn, int *buf )
{
	char s[] = PATH_TIME_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t set_tacho_time_sp( uint8_t sn, int value )
{
	char s[] = PATH_TIME_SP;
	*modp_uitoa10( sn, s + PATH_PREF_LEN ) = '/';

	return ev3_write_int( s, value );
}

const char *ev3_tacho_type( inx_t type_inx )
{
	switch ( type_inx ) {
	case LEGO_EV3_L_MOTOR:
		return "lego-ev3-l-motor";
	case LEGO_EV3_M_MOTOR:
		return "lego-ev3-m-motor";
	case FI_L12_EV3:
		return "fi-l12-ev3";

	}
	return ( STR_unknown_ );
}

inx_t get_tacho_type_inx( uint8_t sn )
{
	char buf[ 64 ];

	if ( !get_tacho_driver_name( sn, buf, sizeof( buf ))) return ( TACHO_TYPE__NONE_ );

	if ( strcmp( buf, "lego-ev3-l-motor" ) == 0 ) return LEGO_EV3_L_MOTOR;
	if ( strcmp( buf, "lego-ev3-m-motor" ) == 0 ) return LEGO_EV3_M_MOTOR;
	if ( strcmp( buf, "fi-l12-ev3" ) == 0 ) return FI_L12_EV3;

	return ( TACHO_TYPE__UNKNOWN_ );
}

size_t get_tacho_desc( uint8_t sn, EV3_TACHO *desc )
{
	uint8_t addr;
	char buf[ 32 ];

	desc->type_inx = get_tacho_type_inx( sn );
	if ( desc->type_inx == TACHO_TYPE__NONE_ ) return ( 0 );

	if ( !get_tacho_port_name( sn, buf, sizeof( buf ))) return ( 0 );

	ev3_parse_port_name( buf, &desc->port, &desc->extport, &addr );
	
	return ( sizeof( EV3_TACHO ));
}

EV3_TACHO *ev3_tacho_desc( uint8_t sn )
{
	if ( sn >= TACHO_DESC__LIMIT_) sn = TACHO_DESC__LIMIT_ - 1;
	return ( ev3_tacho + sn );
}

inx_t ev3_tacho_desc_type_inx( uint8_t sn )
{
	return ( ev3_tacho_desc( sn )->type_inx );
}

uint8_t ev3_tacho_desc_port( uint8_t sn )
{
	return ( ev3_tacho_desc( sn )->port );
}

uint8_t ev3_tacho_desc_extport( uint8_t sn )
{
	return ( ev3_tacho_desc( sn )->extport );
}

char *ev3_tacho_port_name( uint8_t sn, char *buf )
{
	return ( ev3_port_name( ev3_tacho_desc( sn )->port, ev3_tacho_desc( sn )->extport, 0, buf ));
}

bool ev3_search_tacho( inx_t type_inx, uint8_t *sn, uint8_t from )
{
	uint8_t _sn = from;

	while ( _sn < TACHO_DESC__LIMIT_) {
		if ( ev3_tacho[ _sn ].type_inx == type_inx ) {
			*sn = _sn;
			return ( true );
		}
		++_sn;
	}
	*sn = TACHO__NONE_;
	return ( false );
}

bool ev3_search_tacho_plugged_in( uint8_t port, uint8_t extport, uint8_t *sn, uint8_t from )
{
	uint8_t _sn = from;

	while ( _sn < TACHO_DESC__LIMIT_) {
		if ( ev3_tacho[ _sn ].port == port ) {
			if ( extport ) {
				if ( ev3_tacho[ _sn ].extport == extport ) {
					*sn = _sn;
					return ( true );
				}
			} else {
				*sn = _sn;
				return ( true );
			}
		}
		++_sn;
	}
	*sn = TACHO__NONE_;
	return ( false );
}

const char *ev3_tacho_command( inx_t command_inx )
{
	switch ( command_inx ) {
	case LEGO_EV3_L_MOTOR_RUN_FOREVER:
		return "run-forever";
	case LEGO_EV3_L_MOTOR_RUN_TO_ABS_POS:
		return "run-to-abs-pos";
	case LEGO_EV3_L_MOTOR_RUN_TO_REL_POS:
		return "run-to-rel-pos";
	case LEGO_EV3_L_MOTOR_RUN_TIMED:
		return "run-timed";
	case LEGO_EV3_L_MOTOR_RUN_DIRECT:
		return "run-direct";
	case LEGO_EV3_L_MOTOR_STOP:
		return "stop";
	case LEGO_EV3_L_MOTOR_RESET:
		return "reset";

	case LEGO_EV3_M_MOTOR_RUN_FOREVER:
		return "run-forever";
	case LEGO_EV3_M_MOTOR_RUN_TO_ABS_POS:
		return "run-to-abs-pos";
	case LEGO_EV3_M_MOTOR_RUN_TO_REL_POS:
		return "run-to-rel-pos";
	case LEGO_EV3_M_MOTOR_RUN_TIMED:
		return "run-timed";
	case LEGO_EV3_M_MOTOR_RUN_DIRECT:
		return "run-direct";
	case LEGO_EV3_M_MOTOR_STOP:
		return "stop";
	case LEGO_EV3_M_MOTOR_RESET:
		return "reset";

	case FI_L12_EV3_RUN_FOREVER:
		return "run-forever";
	case FI_L12_EV3_RUN_TO_ABS_POS:
		return "run-to-abs-pos";
	case FI_L12_EV3_RUN_TO_REL_POS:
		return "run-to-rel-pos";
	case FI_L12_EV3_RUN_TIMED:
		return "run-timed";
	case FI_L12_EV3_RUN_DIRECT:
		return "run-direct";
	case FI_L12_EV3_STOP:
		return "stop";
	case FI_L12_EV3_RESET:
		return "reset";

	}
	return ( STR_unknown_ );
}

size_t set_tacho_command_inx( uint8_t sn, inx_t command_inx )
{
	return set_tacho_command( sn, ( char* ) ev3_tacho_command( command_inx ));
}

const char *ev3_tacho_stop_command( inx_t stop_command_inx )
{
	switch ( stop_command_inx ) {
	case LEGO_EV3_L_MOTOR_COAST:
		return "coast";
	case LEGO_EV3_L_MOTOR_BRAKE:
		return "brake";
	case LEGO_EV3_L_MOTOR_HOLD:
		return "hold";

	case LEGO_EV3_M_MOTOR_COAST:
		return "coast";
	case LEGO_EV3_M_MOTOR_BRAKE:
		return "brake";
	case LEGO_EV3_M_MOTOR_HOLD:
		return "hold";

	case FI_L12_EV3_COAST:
		return "coast";
	case FI_L12_EV3_BRAKE:
		return "brake";
	case FI_L12_EV3_HOLD:
		return "hold";

	}
	return ( STR_unknown_ );
}

inx_t get_tacho_stop_command_inx( uint8_t sn, inx_t type_inx )
{
	char buf[ 64 ];

	if ( !get_tacho_stop_command( sn, buf, sizeof( buf ))) return ( TACHO_STOP_COMMAND__NONE_ );

	switch ( type_inx ) {
			
	case LEGO_EV3_L_MOTOR:
		if ( strcmp( buf, "coast" ) == 0 ) return LEGO_EV3_L_MOTOR_COAST;
		if ( strcmp( buf, "brake" ) == 0 ) return LEGO_EV3_L_MOTOR_BRAKE;
		if ( strcmp( buf, "hold" ) == 0 ) return LEGO_EV3_L_MOTOR_HOLD;

		break;

	case LEGO_EV3_M_MOTOR:
		if ( strcmp( buf, "coast" ) == 0 ) return LEGO_EV3_M_MOTOR_COAST;
		if ( strcmp( buf, "brake" ) == 0 ) return LEGO_EV3_M_MOTOR_BRAKE;
		if ( strcmp( buf, "hold" ) == 0 ) return LEGO_EV3_M_MOTOR_HOLD;

		break;

	case FI_L12_EV3:
		if ( strcmp( buf, "coast" ) == 0 ) return FI_L12_EV3_COAST;
		if ( strcmp( buf, "brake" ) == 0 ) return FI_L12_EV3_BRAKE;
		if ( strcmp( buf, "hold" ) == 0 ) return FI_L12_EV3_HOLD;

		break;

	}
	return ( TACHO_STOP_COMMAND__UNKNOWN_ );
}

size_t set_tacho_stop_command_inx( uint8_t sn, inx_t stop_command_inx )
{
	return set_tacho_stop_command( sn, ( char* ) ev3_tacho_stop_command( stop_command_inx ));
}

size_t get_tacho_state_flags( uint8_t sn, flags_t *flags )
{
	char buf[ 64 ];
	size_t result;

	result = get_tacho_state( sn, buf, sizeof( buf ));
	if ( result == 0 ) return ( 0 );

	*flags = TACHO_STATE__NONE_;
	if ( result == 1 ) return ( 1 );

	if ( strstr( buf, "running" )) *flags |= TACHO_RUNNING;
	if ( strstr( buf, "ramping" )) *flags |= TACHO_RAMPING;
	if ( strstr( buf, "holding" )) *flags |= TACHO_HOLDING;
	if ( strstr( buf, "stalled" )) *flags |= TACHO_STALLED;

	return ( result );
}

int ev3_tacho_init( void )
{
	char list[ 256 ];
	char *p;
	uint32_t sn;
	int cnt = 0;

	memset( ev3_tacho, 0, sizeof( ev3_tacho ));

	if ( !ev3_listdir( "/sys/class/tacho-motor", list, sizeof( list ))) return ( -1 );

	p = strtok( list, " " );
	while ( p ) {
		if (( ev3_string_suffix( "motor", &p, &sn ) == 1 ) && ( sn < TACHO_DESC__LIMIT_)) {
			get_tacho_desc( sn, ev3_tacho + sn );
			++cnt;
		}
		p = strtok( NULL, " " );
	}
	return ( cnt );
}

