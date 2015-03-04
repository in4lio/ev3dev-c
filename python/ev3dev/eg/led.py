# -*- coding: utf-8 -*-

import sys
from ev3dev import *

print 'Waiting the EV3 brick online...'
if ev3_init() < 1: sys.exit( 1 )

ok, state = get_led_brightness( EV3_RED_LEFT )
if ok:
    print 'get_led_brightness( EV3_RED_LEFT ) =', state
else:
    print 'ERROR: get_led_brightness'

if not set_led_brightness( EV3_RED_LEFT, 0 ):
    print 'ERROR: set_led_brightness'

state = get_led_trigger_inx( EV3_RED_RIGHT )
print 'get_led_trigger_inx( EV3_RED_RIGHT ) =', state

if not set_led_trigger( EV3_RED_RIGHT, 'heartbeat' ):
    print 'ERROR: set_led_trigger'

ev3_uninit()
