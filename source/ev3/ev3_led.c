
/*  ev3_led.c was generated by yup.py (yupp) 0.8b7
    out of ev3_led.yu-c at 2015-07-22 12:16
 *//**
 *  \file  ev3_led.c (ev3_led.yu-c)
 *  \brief  EV3 LEDs.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define EV3_LED_IMPLEMENT

#include <string.h>
#include <stdio.h>
#include "ev3.h"
#include "ev3_led.h"

static const char * const led_attr_brightness[] = {
	"/sys/class/leds/ev3-left1:green:ev3dev/brightness",
	"/sys/class/leds/ev3-right1:green:ev3dev/brightness",
	"/sys/class/leds/ev3-left0:red:ev3dev/brightness",
	"/sys/class/leds/ev3-right0:red:ev3dev/brightness",
	"/sys/class/leds/outA::ev3dev/brightness",
	"/sys/class/leds/outB::ev3dev/brightness",
	"/sys/class/leds/outC::ev3dev/brightness",
	"/sys/class/leds/outD::ev3dev/brightness",

};

static const char * const led_attr_delay_off[] = {
	"/sys/class/leds/ev3-left1:green:ev3dev/delay_off",
	"/sys/class/leds/ev3-right1:green:ev3dev/delay_off",
	"/sys/class/leds/ev3-left0:red:ev3dev/delay_off",
	"/sys/class/leds/ev3-right0:red:ev3dev/delay_off",
	"/sys/class/leds/outA::ev3dev/delay_off",
	"/sys/class/leds/outB::ev3dev/delay_off",
	"/sys/class/leds/outC::ev3dev/delay_off",
	"/sys/class/leds/outD::ev3dev/delay_off",

};

static const char * const led_attr_delay_on[] = {
	"/sys/class/leds/ev3-left1:green:ev3dev/delay_on",
	"/sys/class/leds/ev3-right1:green:ev3dev/delay_on",
	"/sys/class/leds/ev3-left0:red:ev3dev/delay_on",
	"/sys/class/leds/ev3-right0:red:ev3dev/delay_on",
	"/sys/class/leds/outA::ev3dev/delay_on",
	"/sys/class/leds/outB::ev3dev/delay_on",
	"/sys/class/leds/outC::ev3dev/delay_on",
	"/sys/class/leds/outD::ev3dev/delay_on",

};

static const char * const led_attr_max_brightness[] = {
	"/sys/class/leds/ev3-left1:green:ev3dev/max_brightness",
	"/sys/class/leds/ev3-right1:green:ev3dev/max_brightness",
	"/sys/class/leds/ev3-left0:red:ev3dev/max_brightness",
	"/sys/class/leds/ev3-right0:red:ev3dev/max_brightness",
	"/sys/class/leds/outA::ev3dev/max_brightness",
	"/sys/class/leds/outB::ev3dev/max_brightness",
	"/sys/class/leds/outC::ev3dev/max_brightness",
	"/sys/class/leds/outD::ev3dev/max_brightness",

};

static const char * const led_attr_trigger[] = {
	"/sys/class/leds/ev3-left1:green:ev3dev/trigger",
	"/sys/class/leds/ev3-right1:green:ev3dev/trigger",
	"/sys/class/leds/ev3-left0:red:ev3dev/trigger",
	"/sys/class/leds/ev3-right0:red:ev3dev/trigger",
	"/sys/class/leds/outA::ev3dev/trigger",
	"/sys/class/leds/outB::ev3dev/trigger",
	"/sys/class/leds/outC::ev3dev/trigger",
	"/sys/class/leds/outD::ev3dev/trigger",

};

size_t get_led_brightness( uint8_t inx, byte *buf )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_read_byte( led_attr_brightness[ inx ], buf );
}

size_t set_led_brightness( uint8_t inx, byte value )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_write_byte( led_attr_brightness[ inx ], value );
}

size_t get_led_delay_off( uint8_t inx, int *buf )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_read_int( led_attr_delay_off[ inx ], buf );
}

size_t set_led_delay_off( uint8_t inx, int value )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_write_int( led_attr_delay_off[ inx ], value );
}

size_t get_led_delay_on( uint8_t inx, int *buf )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_read_int( led_attr_delay_on[ inx ], buf );
}

size_t set_led_delay_on( uint8_t inx, int value )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_write_int( led_attr_delay_on[ inx ], value );
}

size_t get_led_max_brightness( uint8_t inx, byte *buf )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_read_byte( led_attr_max_brightness[ inx ], buf );
}

size_t get_led_trigger( uint8_t inx, char *buf, size_t sz )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_read_char_array( led_attr_trigger[ inx ], buf, sz );
}

size_t set_led_trigger( uint8_t inx, char *value )
{
	if ( inx >= LED__COUNT_ ) return ( 0 );

	return ev3_write_char_array( led_attr_trigger[ inx ], value );
}

const char *ev3_led_trigger( inx_t trigger_inx )
{
	switch ( trigger_inx ) {
	case TRIGGER_NONE:
		return "none";
	case TRIGGER_MMC0:
		return "mmc0";
	case TRIGGER_TIMER:
		return "timer";
	case TRIGGER_HEARTBEAT:
		return "heartbeat";
	case TRIGGER_DEFAULT_ON:
		return "default-on";
	case TRIGGER_TRANSIENT:
		return "transient";
	case TRIGGER_LEGOEV3_BATTERY_CHARGING_OR_FULL:
		return "legoev3-battery-charging-or-full";
	case TRIGGER_LEGOEV3_BATTERY_CHARGING:
		return "legoev3-battery-charging";
	case TRIGGER_LEGOEV3_BATTERY_FULL:
		return "legoev3-battery-full";
	case TRIGGER_LEGOEV3_BATTERY_CHARGING_BLINK_FULL_SOLID:
		return "legoev3-battery-charging-blink-full-solid";
	case TRIGGER_RFKILL0:
		return "rfkill0";
	case TRIGGER_PHY0RX:
		return "phy0rx";
	case TRIGGER_PHY0TX:
		return "phy0tx";
	case TRIGGER_PHY0ASSOC:
		return "phy0assoc";
	case TRIGGER_PHY0RADIO:
		return "phy0radio";
	case TRIGGER_RFKILL1:
		return "rfkill1";

	}
	return ( STR_unknown_ );
}

inx_t get_led_trigger_inx( uint8_t inx )
{
	char buf[ 256 ];
	char *p;
	uint8_t trigger_inx = 0;

	if ( !get_led_trigger( inx, buf, sizeof( buf ))) return ( TRIGGER__COUNT_ );

	p = strtok( buf, " " );
	while ( p ) {
		if ( *p == '[' ) return ( trigger_inx );
		++trigger_inx;
		p = strtok( NULL, " " );
	}
	return ( TRIGGER__COUNT_ );
}

size_t set_led_trigger_inx( uint8_t inx, inx_t trigger_inx )
{
	return set_led_trigger( inx, ( char* ) ev3_led_trigger( trigger_inx ));
}
