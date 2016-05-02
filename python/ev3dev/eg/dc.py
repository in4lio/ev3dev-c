# -*- coding: utf-8 -*-

from time import sleep
import sys
from ev3dev import *

if __name__ == '__main__':
    print 'Waiting the EV3 brick online...'
    if ev3_init() < 1: sys.exit( 1 )

    print '*** ( EV3 ) Hello! ***'
    ev3_port_init()
    port = OUTPUT_B

    name_port = ev3_port_name( port, EXT_PORT__NONE_, 0 )
    print 'Set mode of the EV3 output port (%s)...' % ( name_port )
    sn_port = ev3_search_port( port, EXT_PORT__NONE_ )
    set_port_mode_inx( sn_port, OUTPUT_RCX_MOTOR )
    ok, mode = get_port_mode( sn_port, 256 )
    if ok:
        print '%s: %s' % ( name_port, mode )
    sleep( 0.2 )

    ev3_dc_init()

    print 'Found DC motors:'
    for i in range( DC_DESC__LIMIT_ ):
        type_inx = ev3_dc_desc_type_inx( i )
        if type_inx != DC_TYPE__NONE_:
            print '  type =', ev3_dc_type( type_inx )
            print '  port =', ev3_dc_port_name( i )

    ok, sn = ev3_search_dc_plugged_in( port, EXT_PORT__NONE_ )
    if ok:
        print 'DC motor is found, run for 5 sec...'
        set_dc_ramp_up_sp( sn, 2000 )
        set_dc_duty_cycle_sp( sn, 100 )
        set_dc_stop_action_inx( sn, DC_COAST )
        set_dc_command_inx( sn, DC_RUN_FOREVER )
        ok, state = get_dc_state( sn, 256 )
        if ok:
            print 'state:', state
        sleep( 5.0 )
        set_dc_command_inx( sn, DC_STOP )
        ok, state = get_dc_state( sn, 256 )
        if ok:
            print 'state:', state
    else:
        print 'DC motor is NOT found'

    sleep( 0.2 )
    print 'Reset mode of the EV3 output port...'
    set_port_mode_inx( sn_port, OUTPUT_AUTO )
    ok, mode = get_port_mode( sn_port, 256 )
    if ok:
        print '%s: %s' % ( name_port, mode )

    ev3_uninit()
    print '*** ( EV3 ) Bye! ***'
