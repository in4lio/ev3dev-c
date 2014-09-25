
/*  ev3_tacho.h was generated by yup.py (yupp) 0.7b5
    out of ev3_tacho.yu-h at 2014-09-25 18:00
 *//**
 *  \file  ev3_tacho.h (ev3_tacho.yu-h)
 *  \brief  EV3 tacho-motors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef EV3_TACHO_H
#define EV3_TACHO_H

#ifdef  EV3_TACHO_IMPLEMENT
#define EV3_TACHO_EXT
#define EV3_TACHO_EXT_INIT( dec, init ) \
	dec = init
#else
#define EV3_TACHO_EXT extern
#define EV3_TACHO_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup ev3_tacho EV3 tacho-motors
 *  \{
 */

/**
 *  \brief EV3 ports to plug in a tacho.
 */
enum {
	OUTPUT_A,
	OUTPUT_B,
	OUTPUT_C,
	OUTPUT_D,

	OUTPUT__COUNT_  /**< Count of EV3 "out" ports. */
};

/**
 *  \brief Structure of a tacho descriptor.
 */
typedef struct {
	bool     connected;  /**< Flag - the tacho is connected. */
	uint32_t id;         /**< Identifier of the tacho. */
	uint32_t type_id;    /**< The tacho type. */

} EV3_TACHO;

/**
 *  \brief Vector of tacho descriptors for each port (filled by \ref ev3_tacho_init).
 */
EV3_TACHO_EXT EV3_TACHO ev3_tacho[ OUTPUT__COUNT_ ];

/**
 *  \brief Types of tachos.
 */
enum {
	TACHO = 7,
	MINITACHO = 8,

};

/**
 *  \brief Get "duty_cycle" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_duty_cycle( uint8_t id, int *buf );

/**
 *  \brief Get "duty_cycle_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_duty_cycle_sp( uint8_t id, int *buf );
/**
 *  \brief Set "duty_cycle_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_duty_cycle_sp( uint8_t id, int value );

/**
 *  \brief Get "polarity_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_polarity_mode( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "port_name" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_port_name( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "position" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_position( uint8_t id, int *buf );
/**
 *  \brief Set "position" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_position( uint8_t id, int value );

/**
 *  \brief Get "position_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_position_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "position_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_position_mode( uint8_t id, char *value );

/**
 *  \brief Get "position_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_position_sp( uint8_t id, int *buf );
/**
 *  \brief Set "position_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_position_sp( uint8_t id, int value );

/**
 *  \brief Get "pulses_per_second" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_pulses_per_second( uint8_t id, int *buf );

/**
 *  \brief Get "pulses_per_second_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_pulses_per_second_sp( uint8_t id, int *buf );
/**
 *  \brief Set "pulses_per_second_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_pulses_per_second_sp( uint8_t id, int value );

/**
 *  \brief Get "ramp_down_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_ramp_down_sp( uint8_t id, dword *buf );
/**
 *  \brief Set "ramp_down_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_ramp_down_sp( uint8_t id, dword value );

/**
 *  \brief Get "ramp_up_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_ramp_up_sp( uint8_t id, dword *buf );
/**
 *  \brief Set "ramp_up_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_ramp_up_sp( uint8_t id, dword value );

/**
 *  \brief Get "regulation_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_regulation_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "regulation_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_regulation_mode( uint8_t id, char *value );

/**
 *  \brief Set "reset" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_reset( uint8_t id, bool value );

/**
 *  \brief Get "run" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_run( uint8_t id, bool *buf );
/**
 *  \brief Set "run" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_run( uint8_t id, bool value );

/**
 *  \brief Get "run_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_run_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "run_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_run_mode( uint8_t id, char *value );

/**
 *  \brief Get "speed_regulation_D" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_speed_regulation_D( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_D" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_speed_regulation_D( uint8_t id, int value );

/**
 *  \brief Get "speed_regulation_I" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_speed_regulation_I( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_I" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_speed_regulation_I( uint8_t id, int value );

/**
 *  \brief Get "speed_regulation_K" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_speed_regulation_K( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_K" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_speed_regulation_K( uint8_t id, int value );

/**
 *  \brief Get "speed_regulation_P" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_speed_regulation_P( uint8_t id, int *buf );
/**
 *  \brief Set "speed_regulation_P" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_speed_regulation_P( uint8_t id, int value );

/**
 *  \brief Get "state" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_state( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "stop_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_stop_mode( uint8_t id, char *buf, size_t sz );
/**
 *  \brief Set "stop_mode" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.
 *  \param sz Size of attribute value.
 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_stop_mode( uint8_t id, char *value );

/**
 *  \brief Get "stop_modes" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_stop_modes( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get "time_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.

 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_time_sp( uint8_t id, dword *buf );
/**
 *  \brief Set "time_sp" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param value Attribute value.

 *  \return Count of written bytes.
 */
EV3_TACHO_EXT size_t set_tacho_time_sp( uint8_t id, dword value );

/**
 *  \brief Get "type" attribute of the tacho.
 *  \param id Identifier of the tacho.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_TACHO_EXT size_t get_tacho_type( uint8_t id, char *buf, size_t sz );

/**
 *  \brief Get the name of the specified tacho type.
 *  \param type_id The tacho type.
 *  \return Name of the tacho type.
 */
EV3_TACHO_EXT char *ev3_tacho_type( uint8_t type_id );

/**
 *  \brief Search the port of the specified tacho type.
 *  \param type_id The tacho type.
 *  \return EV3 port.
 */
EV3_TACHO_EXT int ev3_tacho_port( uint8_t type_id );

/**
 *  \brief Get the descriptor of a tacho connected to the specified port.
 *  \param port EV3 port.
 *  \return Pointer to the tacho descriptor.
 */
EV3_TACHO_EXT EV3_TACHO *ev3_get_tacho( uint8_t port );

/**
 *  \brief Auto-detection of connected tacho-motors.
 *  \return The number of found tacho-motors or EV3_NONE in case of an error.
 */
EV3_TACHO_EXT int ev3_tacho_init( void );

/** \} */

#ifdef __cplusplus
}
#endif

#endif

