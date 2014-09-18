# -*- coding: utf-8 -*-
#pylint: skip-file

import sys
from ev3dev import *

if ev3_init() == EV3_NONE: sys.exit( 1 )

ok, ls = ev3_listdir( '/sys/class/leds', 256 )
print ls if ok else 'ERROR: ev3_listdir'

ok, state = ev3_read_int( '/sys/class/leds/ev3:red:left/brightness' )
if ok:
    ev3_write_bool( '/sys/class/leds/ev3:red:left/brightness', not state )
else:
    print 'ERROR: ev3_write_bool'

ok, trig = ev3_read( '/sys/class/leds/ev3:red:right/trigger', 256 )
print trig if ok else 'ERROR: ev3_read_binary'

ev3_write( '/sys/class/leds/ev3:red:right/trigger', 'heartbeat' )

ev3_uninit()
