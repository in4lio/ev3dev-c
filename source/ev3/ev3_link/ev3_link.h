/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  ev3_link.h
 *  \brief  EV3 remote access.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

/** \page udp The interchange protocol over UDP
    \brief Description of message formats for a remote access to the EV3 brick.

Also see
<A HREF="https://github.com/in4lio/ev3dev-c/tree/master/source/ev3/ev3_link">"source/ev3/ev3_link/README"</A>.

<H3>Write data into the specified file on the EV3 brick</H3>

Host application command
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_WRITE_FILE              |
|  2 .. 3                           |  Message counter (id)             |
|  4 .. 5                           |  Filename size (f_sz)             |
|  6 .. 7                           |  Data size (d_sz)                 |
|  8 .. 8 + f_sz - 1                |  Filename                         |
|  8 + f_sz .. 8 + f_sz + d_sz - 1  |  Data                             |

Brick server reply
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_RESULT_WRITE            |
|  2 .. 3                           |  id                               |
|  4 .. 5                           |  0                                |
|  6 .. 7                           |  Count of written bytes           |

<HR>
<H3>Write data into several specified files on the EV3 brick</H3>

Host application command
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_WRITE_FILE              |
|  2 .. 3                           |  Message counter (id)             |
|  4 .. 5                           |  Filename size (f_sz)             |
|  6 .. 7                           |  Data size (d_sz)                 |
|  8                                |  Sequence number 1                |
|  9                                |  SN 2                             |
|  10                               |  SN 3                             |
|  11                               |  SN 4                             |
|  12 .. 13                         |  Position of SN in template       |
|  14 .. 14 + f_sz - 1              |  Filename (template)              |
|  14 + f_sz .. 14 + f_sz + d_sz - 1|  Data                             |

Brick server reply
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_RESULT_WRITE            |
|  2 .. 3                           |  id                               |
|  4 .. 5                           |  0                                |
|  6 .. 7                           |  Count of written bytes           |

<HR>
<H3>Read data from the specified file on the EV3 brick</H3>

Host application command
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_READ_FILE               |
|  2 .. 3                           |  Message counter (id)             |
|  4 .. 5                           |  Filename size (f_sz)             |
|  6 .. 7                           |  Max data size                    |
|  8 .. 8 + f_sz - 1                |  Filename                         |

Brick server reply
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_DATA_READ               |
|  2 .. 3                           |  id                               |
|  4 .. 5                           |  0                                |
|  6 .. 7                           |  Count of read bytes (d_sz)       |
|  8 .. 8 + d_sz - 1                |  Data                             |

<HR>
<H3>List files in the specified directory on the EV3 brick</H3>

Host application command
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_LIST_DIR                |
|  2 .. 3                           |  Message counter (id)             |
|  4 .. 5                           |  Directory name size (f_sz)       |
|  6 .. 7                           |  Max files list size              |
|  8 .. 8 + f_sz - 1                |  Directory name                   |

Brick server reply
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_DIRECTORY               |
|  2 .. 3                           |  id                               |
|  4 .. 5                           |  0                                |
|  6 .. 7                           |  Files list size (d_sz)           |
|  8 .. 8 + d_sz - 1                |  Files list                       |

<HR>
<H3>Power-off the EV3 brick</H3>

Host application command
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_POWEROFF                |
|  2 .. 3                           |  Message counter (id)             |
|  4 .. 5                           |  0x5555                           |
|  6 .. 7                           |  0xAAAA                           |

Brick server reply
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_COMPLETION              |
|  2 .. 3                           |  id                               |
|  4 .. 5                           |  0                                |
|  6 .. 7                           |  0                                |

<HR>
<H3>Notify a host that the brick server is online</H3>

Brick server beacon
| Bytes                             |  Content                          |
|:--------------------------------- |:--------------------------------- |
|  0 .. 1                           |  \ref EV3_WELCOME                 |
|  2 .. 3                           |  0                                |
|  4 .. 5                           |  0                                |
|  6 .. 7                           |  0                                |
 */

#pragma once

#include <stdint.h>

/**
 *  \defgroup ev3_link Remote access
 *  \brief Remote access to the EV3 brick over UDP.
 *  \{
 */

/**
 *  \brief Open an UDP socket.
 *  \param addr IP address of the EV3 brick.
 *  \param port UDP port.
 *  \return 0 - finished successfully, EOF - an error has occurred.
 */
extern int udp_ev3_open( char *addr, uint16_t port );

/**
 *  \brief Close an UDP socket.
 *  \return 0 - finished successfully, EOF - an error has occurred.
 */
extern int udp_ev3_close( void );

/**
 *  \brief Check for a beacon from the EV3 brick.
 *  \return 0 - no beacon, 1 - beacon has been received.
 */
extern int udp_ev3_catch_address( void );

/**
 *  \brief Read data from the specified file over UDP.
 *  \param fn Filename.
 *  \param[out] buf Buffer for data.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern int udp_ev3_read( char *fn, void *buf, int sz );

/**
 *  \brief Write data into the specified file over UDP.
 *  \param fn Filename.
 *  \param data Data.
 *  \param sz Data size.
 *  \return Count of written bytes.
 */
extern int udp_ev3_write( char *fn, void *data, int sz );

/**
 *  \brief Write data into the group of specified files over UDP.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param pos Position of the sequence number field into the template.
 *  \param fn Filename template.
 *  \param data Data.
 *  \param sz Data size.
 *  \return Count of written bytes.
 */
extern int udp_ev3_multi_write( uint8_t *sn, uint16_t pos, char *fn, void *data, int sz );

/**
 *  \brief List files in the specified directory over UDP.
 *  \param fn Directory name.
 *  \param[out] buf Buffer for files list.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
extern int udp_ev3_listdir( char *fn, void *buf, int sz );

/**
 *  \brief Read state of EV3 brick keys over UDP.
 *  \param[out] buf Buffer for data.
 *  \return Count of read bytes.
 */
extern int udp_ev3_read_keys( uint8_t *buf );

/**
 *  \brief Power-off the EV3 brick.
 *  \return 0 - no reply, 1 - OK.
 */
extern int udp_ev3_poweroff( void );

/** \} */
