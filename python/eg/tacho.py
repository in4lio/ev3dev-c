# -*- coding: utf-8 -*-
#pylint: skip-file

from time import sleep
import sys
sys.path.append( '..' )
from ev3dev import *

if __name__ == '__main__':
    if not EV3_BRICK:
        # Disable auto-detection of the brick (you have to set the correct address below)
        ev3.brick_addr = '192.168.0.204'
    if ev3_init() == EV3_NONE: sys.exit( 1 )

    if not EV3_BRICK:
        print 'The EV3 brick auto-detection is DISABLED, waiting %s online...' % ( ev3.brick_addr )

    while ev3_tacho_init() == EV3_NONE: sleep( 1.0 )

    print '*** ( EV3 ) Hello! ***'

    print 'Found tacho-motors:'
    for i in range( OUTPUT__COUNT_ ):
        desc = ev3_get_tacho( i )
        if desc.connected:
            print '  port = out%d' % ( i + 1 )
            ok, _type = get_tacho_type( desc.type_id, 256 )
            if ok:
                print '  type =', _type
    # Look for minitacho motor
    p = ev3_tacho_port( MINITACHO )
    if p != EV3_NONE:
        _id = ev3_get_tacho( p ).id

        print 'MINITACHO is found, run for 5 sec...'
        set_tacho_regulation_mode( _id, "off" )
        set_tacho_run_mode( _id, "time" )
        set_tacho_stop_mode( _id, "brake" )
        set_tacho_duty_cycle_sp( _id, 100 )
        set_tacho_time_sp( _id, 5000 )
        set_tacho_ramp_up_sp( _id, 2000 )
        set_tacho_ramp_down_sp( _id, 2000 )
        set_tacho_run( _id, True )
    else:
        print 'MINITACHO is not found'

    ev3_uninit()
    print '*** ( EV3 ) Bye! ***'
