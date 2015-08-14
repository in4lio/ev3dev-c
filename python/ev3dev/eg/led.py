# -*- coding: utf-8 -*-

import sys
from ev3dev import *

print 'Waiting the EV3 brick online...'
if ev3_init() < 1: sys.exit( 1 )

ok, state = get_led_brightness( EV3_LEFT_RED )
if ok:
    print 'get_led_brightness( EV3_LEFT_RED ) =', state
else:
    print 'ERROR: get_led_brightness()'

if not set_led_brightness( EV3_LEFT_RED, 0 ):
    print 'ERROR: set_led_brightness()'

state = get_led_trigger_inx( EV3_RIGHT_RED )
print 'get_led_trigger_inx( EV3_RIGHT_RED ) =', state

if not set_led_trigger( EV3_RIGHT_RED, 'heartbeat' ):
    print 'ERROR: set_led_trigger()'

ev3_uninit()
