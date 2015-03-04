# -*- coding: utf-8 -*-

from time import sleep
import sys
from ev3dev import *

if __name__ == '__main__':
    if not EV3_BRICK:
        # Disable auto-detection of the brick (you have to set the correct address below)
        ev3.brick_addr = '192.168.0.204'

    if ev3_init() == -1: sys.exit( 1 )

    if not EV3_BRICK:
        print 'The EV3 brick auto-detection is DISABLED, waiting %s online with plugged tacho...' % ( ev3.brick_addr )

    while ev3_tacho_init() < 1: sleep( 1.0 )

    print '*** ( EV3 ) Hello! ***'

    print 'Found tacho motors:'
    for i in range( TACHO_DESC__LIMIT_ ):
        type_inx = ev3_tacho_desc_type_inx( i )
        if type_inx != TACHO_TYPE__NONE_:
            print '  type =', ev3_tacho_type( type_inx )
            print '  port =', ev3_port_name( ev3_tacho_desc_port( i ), ev3_tacho_desc_extport( i ))

    ok, sn = ev3_search_tacho( MINITACHO )
    if ok:
        print 'MINITACHO motor is found, run for 5 sec...'
        set_tacho_regulation_mode( sn, 'off' )
        set_tacho_run_mode( sn, 'time' )
        set_tacho_stop_mode( sn, 'brake' )
        set_tacho_duty_cycle_sp( sn, 100 )
        set_tacho_time_sp( sn, 5000 )
        set_tacho_ramp_up_sp( sn, 2000 )
        set_tacho_ramp_down_sp( sn, 2000 )
        set_tacho_run( sn, True )
    else:
        print 'MINITACHO motor is NOT found'

    ev3_uninit()
    print '*** ( EV3 ) Bye! ***'
