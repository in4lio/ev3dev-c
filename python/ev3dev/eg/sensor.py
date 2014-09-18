# -*- coding: utf-8 -*-
#pylint: skip-file

from time import sleep
import sys
from ev3dev import *

color = [ '?', 'BLACK', 'BLUE', 'GREEN', 'YELLOW', 'RED', 'WHITE', 'BROWN' ]

def _touch_pressed( id ):
    return ( get_sensor_value( 0, id )[ 1 ] != 0 )

if __name__ == '__main__':
    print 'Waiting the EV3 brick online...'
    if ev3_init() == EV3_NONE: sys.exit( 1 )

    print '*** ( EV3 ) Hello! ***'
    ev3_sensor_init();

    print 'Found sensors:'
    for i in range( INPUT__COUNT_ ):
        desc = ev3_get_sensor( i )
        if desc.connected:
            print '  port = in%d' % ( i + 1 )
            _type = ev3_sensor_type( desc.type_id )
            if _type:
                print '  type =', _type
            else:
                print '  type_id =', desc.type_id
            ok, mode = get_sensor_mode( desc.id, 256 )
            if ok:
                print '  mode =', mode
            ok, n = get_sensor_num_values( desc.id )
            if ok:
                for ii in range( n ):
                    ok, val = get_sensor_value( ii, desc.id )
                    if ok:
                        print '  value%d = %d' % ( ii, val )
    # Look for touch sensor
    p_touch = ev3_sensor_port( EV3_TOUCH )
    if p_touch != EV3_NONE:
        print 'EV3_TOUCH is found, press BUTTON for EXIT...'
        id_touch = ev3_get_sensor( p_touch ).id
        # Look for color sensor
        p_color = ev3_sensor_port( EV3_COLOR )
        if p_color != EV3_NONE:
            id_color = ev3_get_sensor( p_color ).id
            print 'EV3_COLOR is found, reading COLOR...'
            set_sensor_mode( id_color, 'COL-COLOR' )
            while ( 1 ):
                # Read color sensor value
                ok, val = get_sensor_value( 0, id_color )
                if not ok or ( val < 0 ) or ( val >= len( color )):
                    val = 0
                sys.stdout.write( '\r(%s)' % ( color[ val ]))
                sys.stdout.flush()
                # Check touch pressed
                if _touch_pressed( id_touch ):
                    break
                sleep( 0.2 )
                sys.stdout.write( '\r        ' )
                sys.stdout.flush()
                if _touch_pressed( id_touch ):
                    break
                sleep( 0.2 )
        else:
            print 'EV3_COLOR is not found'
            # Wait touch pressed
            while not _touch_pressed( id_touch ):
                sleep( 0.2 )
    else:
        print 'EV3_TOUCH is not found'
        sys.exit( 0 )

    ev3_uninit()
    print
    print '*** ( EV3 ) Bye! ***'
