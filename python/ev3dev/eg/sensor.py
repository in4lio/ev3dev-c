# -*- coding: utf-8 -*-

from time import sleep
import sys
from ev3dev import *

color = [ '?', 'BLACK', 'BLUE', 'GREEN', 'YELLOW', 'RED', 'WHITE', 'BROWN' ]

def _check_pressed( sn ):
    if sn == SENSOR__NONE_:
        ok, val = ev3_read_keys()
        return ( ok and (( val & EV3_KEY_UP ) != 0 ))
    else:
        ok, val = get_sensor_value( 0, sn )
        return ( ok and ( val != 0 ))

if __name__ == '__main__':
    print 'Waiting the EV3 brick online...'
    if ev3_init() < 1: sys.exit( 1 )

    print '*** ( EV3 ) Hello! ***'
    ev3_sensor_init()

    print 'Found sensors:'
    for i in range( SENSOR_DESC__LIMIT_ ):
        type_inx = ev3_sensor_desc_type_inx( i )
        if type_inx != SENSOR_TYPE__NONE_:
            print '  type =', ev3_sensor_type( type_inx )
            print '  port =', ev3_sensor_port_name( i )
            ok, mode = get_sensor_mode( i, 256 )
            if ok:
                print '  mode =', mode
            ok, n = get_sensor_num_values( i )
            if ok:
                for ii in range( n ):
                    ok, val = get_sensor_value( ii, i )
                    if ok:
                        print '  value%d = %d' % ( ii, val )

    ok, sn_ir = ev3_search_sensor( LEGO_EV3_IR )
    if ok:
        print 'IR sensor is found'
    else:
        print 'IR sensor is NOT found'

    ok, sn_touch = ev3_search_sensor( LEGO_EV3_TOUCH )
    if ok:
        print 'TOUCH sensor is found, press BUTTON for EXIT...'
    else:
        print 'TOUCH sensor is NOT found, press UP on the EV3 brick for EXIT...'

    ok, sn_color = ev3_search_sensor( LEGO_EV3_COLOR )
    if ok:
        print 'COLOR sensor is found, reading COLOR...'
        set_sensor_mode( sn_color, 'COL-COLOR' )
        while ( 1 ):
            ok, val = get_sensor_value( 0, sn_color )
            if not ok or ( val < 0 ) or ( val >= len( color )):
                val = 0
            sys.stdout.write( '\r(%s)' % ( color[ val ]))
            sys.stdout.flush()
            if _check_pressed( sn_touch ):
                break
            sleep( 0.2 )
            sys.stdout.write( '\r        ' )
            sys.stdout.flush()
            if _check_pressed( sn_touch ):
                break
            sleep( 0.2 )
    else:
        print 'COLOR sensor is NOT found'
        while not _check_pressed( sn_touch ):
            sleep( 0.1 )

    ev3_uninit()
    print
    print '*** ( EV3 ) Bye! ***'
