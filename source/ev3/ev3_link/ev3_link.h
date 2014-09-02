/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  ev3_link.h
 *  \brief  EV3 remote access.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  The MIT License
 */

#pragma once

extern int udp_ev3_open( char *addr, uint16_t port );
extern int udp_ev3_read( char *fn, void *buf, int sz );
extern int udp_ev3_write( char *fn, void *data, int sz );
extern int udp_ev3_listdir( char *fn, void *buf, int sz );
extern int udp_ev3_poweroff( void );
