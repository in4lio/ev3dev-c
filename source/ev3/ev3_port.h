
/*  ev3_port.h was generated by yup.py (yupp) 0.8b7
    out of ev3_port.yu-h at 2015-07-22 12:14
 *//**
 *  \file  ev3_port.h (ev3_port.yu-h)
 *  \brief  EV3 Ports.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef EV3_PORT_H
#define EV3_PORT_H

#ifdef  EV3_PORT_IMPLEMENT
#define EV3_PORT_EXT
#define EV3_PORT_EXT_INIT( dec, init ) \
	dec = init
#else
#define EV3_PORT_EXT extern
#define EV3_PORT_EXT_INIT( dec, init ) \
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
 *  \defgroup ev3_port EV3 Ports and Extended Ports
 *  \brief Access to EV3 Ports and Extended Ports.
 *  \see http://www.ev3dev.org/docs/ports/
 *  \see http://www.ev3dev.org/docs/drivers/lego-port-class/
 *  \{
 */

#define PORT_DIR  "/sys/class/lego-port"  /**< Directory of EV3 ports. */

/**
 *  \brief Structure of a EV3 port descriptor.
 */
typedef struct {
	inx_t type_inx;  /**< EV3 port type. */
	uint8_t port;  /**< EV3 port EV3 port. */
	uint8_t extport;  /**< EV3 port extended port. */
	uint8_t addr;  /**< EV3 port address. */

} EV3_PORT;

#define PORT_DESC__LIMIT_  64  /**< Limit of EV3 port descriptors. */

#define PORT__NONE_  PORT_DESC__LIMIT_  /**< EV3 port is not found. */

/**
 *  \brief Vector of EV3 port descriptors (filled by \ref ev3_port_init).
 */
EV3_PORT_EXT EV3_PORT ev3_port[ PORT_DESC__LIMIT_ ];

/**
 *  \brief Identifiers of EV3 port types.
 */
enum {
	PORT_TYPE__NONE_ = 0,  /* XXX: memset( 0 ) is used */

	HT_NXT_SMUX_PORT,
	LEGOEV3_INPUT_PORT,
	LEGOEV3_OUTPUT_PORT,
	MS_EV3_SMUX_PORT,
	WEDO_PORT,

	PORT_TYPE__COUNT_,  /**< Count of EV3 port types. */
	PORT_TYPE__UNKNOWN_ = PORT_TYPE__COUNT_
};

/**
 *  \brief Identifiers of EV3 port modes.
 */
enum {
	PORT_MODE__NONE_ = 0,

	HT_NXT_SMUX_PORT_ANALOG, HT_NXT_SMUX_ANALOG = HT_NXT_SMUX_PORT_ANALOG,				
	HT_NXT_SMUX_PORT_I2C, HT_NXT_SMUX_I2C = HT_NXT_SMUX_PORT_I2C,
							
	LEGOEV3_INPUT_PORT_AUTO, INPUT_AUTO = LEGOEV3_INPUT_PORT_AUTO,				
	LEGOEV3_INPUT_PORT_NXT_ANALOG, INPUT_NXT_ANALOG = LEGOEV3_INPUT_PORT_NXT_ANALOG,				
	LEGOEV3_INPUT_PORT_NXT_COLOR, INPUT_NXT_COLOR = LEGOEV3_INPUT_PORT_NXT_COLOR,				
	LEGOEV3_INPUT_PORT_NXT_I2C, INPUT_NXT_I2C = LEGOEV3_INPUT_PORT_NXT_I2C,				
	LEGOEV3_INPUT_PORT_EV3_ANALOG, INPUT_EV3_ANALOG = LEGOEV3_INPUT_PORT_EV3_ANALOG,				
	LEGOEV3_INPUT_PORT_EV3_UART, INPUT_EV3_UART = LEGOEV3_INPUT_PORT_EV3_UART,				
	LEGOEV3_INPUT_PORT_OTHER_UART, INPUT_OTHER_UART = LEGOEV3_INPUT_PORT_OTHER_UART,				
	LEGOEV3_INPUT_PORT_RAW, INPUT_RAW = LEGOEV3_INPUT_PORT_RAW,
							
	LEGOEV3_OUTPUT_PORT_AUTO, OUTPUT_AUTO = LEGOEV3_OUTPUT_PORT_AUTO,				
	LEGOEV3_OUTPUT_PORT_EV3_TACHO_MOTOR, OUTPUT_EV3_TACHO_MOTOR = LEGOEV3_OUTPUT_PORT_EV3_TACHO_MOTOR,				
	LEGOEV3_OUTPUT_PORT_RCX_MOTOR, OUTPUT_RCX_MOTOR = LEGOEV3_OUTPUT_PORT_RCX_MOTOR,				
	LEGOEV3_OUTPUT_PORT_RCX_LED, OUTPUT_RCX_LED = LEGOEV3_OUTPUT_PORT_RCX_LED,				
	LEGOEV3_OUTPUT_PORT_RAW, OUTPUT_RAW = LEGOEV3_OUTPUT_PORT_RAW,
							
	MS_EV3_SMUX_PORT_UART, MS_EV3_SMUX_UART = MS_EV3_SMUX_PORT_UART,				
	MS_EV3_SMUX_PORT_ANALOG, MS_EV3_SMUX_ANALOG = MS_EV3_SMUX_PORT_ANALOG,
							
	WEDO_PORT_AUTO, WEDO_AUTO = WEDO_PORT_AUTO,

	PORT_MODE__COUNT_,  /**< Count of EV3 port modes. */
	PORT_MODE__UNKNOWN_ = PORT_MODE__COUNT_
};

/**
 *  \brief Read "driver_name" attribute of the EV3 port.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_PORT_EXT size_t get_port_driver_name( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Read "mode" attribute of the EV3 port.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_PORT_EXT size_t get_port_mode( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Write "mode" attribute of the EV3 port.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_PORT_EXT size_t set_port_mode( uint8_t sn, char *value );

/**
 *  \brief Read "modes" attribute of the EV3 port.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_PORT_EXT size_t get_port_modes( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Read "port_name" attribute of the EV3 port.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_PORT_EXT size_t get_port_port_name( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Write "set_device" attribute of the EV3 port.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
EV3_PORT_EXT size_t set_port_set_device( uint8_t sn, char *value );

/**
 *  \brief Read "status" attribute of the EV3 port.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
EV3_PORT_EXT size_t get_port_status( uint8_t sn, char *buf, size_t sz );

/**
 *  \brief Get name of the specified EV3 port type.
 *  \param type_inx Index of the EV3 port type.
 *  \return Requested value.
 */
EV3_PORT_EXT const char *ev3_port_type( inx_t type_inx );

/**
 *  \brief Read "driver_name" attribute and get index of the EV3 port type.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_PORT_EXT inx_t get_port_type_inx( uint8_t sn );

/**
 *  \brief Read the EV3 port attributes that are required for filling the descriptor.
 *  \param sn Sequence number.
 *  \param desc Buffer for the descriptor.
 *  \return Count of read bytes.
 */
EV3_PORT_EXT size_t get_port_desc( uint8_t sn, EV3_PORT *desc );

/**
 *  \brief Get descriptor of the EV3 port.
 *  \param sn Sequence number.
 *  \return Pointer to the EV3 port descriptor.
 */
EV3_PORT_EXT EV3_PORT *ev3_port_desc( uint8_t sn );

/**
 *  \brief Get type from the EV3 port descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_PORT_EXT inx_t ev3_port_desc_type_inx( uint8_t sn );

/**
 *  \brief Get EV3 port from the EV3 port descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_PORT_EXT uint8_t ev3_port_desc_port( uint8_t sn );

/**
 *  \brief Get extended port from the EV3 port descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_PORT_EXT uint8_t ev3_port_desc_extport( uint8_t sn );

/**
 *  \brief Get address from the EV3 port descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
EV3_PORT_EXT uint8_t ev3_port_desc_addr( uint8_t sn );

/**
 *  \brief Assemble EV3 port name from the EV3 port descriptor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \return Requested value.
 */
EV3_PORT_EXT char *ev3_port_port_name( uint8_t sn, char *buf );

/**
 *  \brief Search of a sequence number of the specified EV3 port type.
 *  \param type_inx The EV3 port type.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the EV3 port is found.
 */
EV3_PORT_EXT bool ev3_search_port_type( inx_t type_inx, uint8_t *sn, uint8_t from );

/**
 *  \brief Search of a sequence number the EV3 port by plug-in attributes.
 *  \param port EV3 port.
 *  \param extport Extended port.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the EV3 port is found.
 */
EV3_PORT_EXT bool ev3_search_port_plugged_in( uint8_t port, uint8_t extport, uint8_t *sn, uint8_t from );

/**
 *  \brief Get name of the specified EV3 port mode.
 *  \param mode_inx Index of the EV3 port mode.
 *  \return Requested value.
 */
EV3_PORT_EXT const char *ev3_port_mode( inx_t mode_inx );

/**
 *  \brief Read "mode" attribute of the EV3 port and get the index.
 *  \param sn Sequence number.
 *  \param type_inx Index of the EV3 port type.
 *  \return Requested value.
 */
EV3_PORT_EXT inx_t get_port_mode_inx( uint8_t sn, inx_t type_inx );

/**
 *  \brief Write "mode" attribute of the EV3 port by the index.
 *  \param sn Sequence number.
 *  \param mode_inx Index of the EV3 port mode.
 *  \return Count of written bytes.
 */
EV3_PORT_EXT size_t set_port_mode_inx( uint8_t sn, inx_t mode_inx );

/**
 *  \brief Detect connected EV3 ports.
 *  \return The number of found EV3 ports or -1 in case of an error.
 */
EV3_PORT_EXT int ev3_port_init( void );

/**
 *  \brief Identifiers of EV3 ports and extended ports.
 */
#define EV3_PORT__NONE_  0  /* XXX: 0 is used */
#define EXT_PORT__NONE_  EV3_PORT__NONE_

#define INPUT_1  '1'			
#define INPUT_2  '2'			
#define INPUT_3  '3'			
#define INPUT_4  '4'	

#define OUTPUT_A  'A'			
#define OUTPUT_B  'B'			
#define OUTPUT_C  'C'			
#define OUTPUT_D  'D'	

#define MUX_1  '1'			
#define MUX_2  '2'			
#define MUX_3  '3'			
#define MUX_4  '4'	

#define SERVO__OFFSET_  16
					
#define SERVO_1  'A'			
#define SERVO_2  'B'			
#define SERVO_3  'C'			
#define SERVO_4  'D'			
#define SERVO_5  'E'			
#define SERVO_6  'F'			
#define SERVO_7  'G'			
#define SERVO_8  'H'	

#define WEDO__OFFSET_  48
					
#define WEDO_1  'a'			
#define WEDO_2  'b'			
#define WEDO_3  'c'			
#define WEDO_4  'd'

/**
 *  \brief Search of a port sequence number by the EV3 port and the extended port.
 *  \param port EV3 port index.
 *  \param extport Extended port index.
 *  \return Port sequence number.
 */
EV3_PORT_EXT uint8_t ev3_search_port( uint8_t port, uint8_t extport );

/**
 *  \brief Parse name of the EV3 port.
 *  \param name Port name.
 *  \param port Buffer for the EV3 port index.
 *  \param extport Buffer for the extended port index.
 *  \param addr Buffer for the address.
 */
EV3_PORT_EXT void ev3_parse_port_name( char *name, uint8_t *port, uint8_t *extport, uint8_t *addr );

/**
 *  \brief Assemble name of the EV3 port.
 *  \param port EV3 port index.
 *  \param extport Extended port index.
 *  \param addr Address.
 *  \param[out] buf Buffer for result.
 *  \return Requested value.
 */
EV3_PORT_EXT char *ev3_port_name( uint8_t port, uint8_t extport, uint8_t addr, char *buf );

/** \} */

#ifdef __cplusplus
}
#endif

#endif

