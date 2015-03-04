# -*- coding: utf-8 -*-

import sys
from ev3dev import *

if ev3_init() < 1: sys.exit( 1 )

ok, ls = ev3_listdir( '/sys/class/leds', 256 )
if ok:
	print 'leds folder:', ls
else:
	print 'ERROR: ev3_listdir'

ok, state = ev3_read_int( '/sys/class/leds/ev3:red:left/brightness' )
if ok:
    ev3_write_int( '/sys/class/leds/ev3:red:left/brightness', 0 if state else 255 )
else:
    print 'ERROR: ev3_read_int'

ok, ls = ev3_listdir( '/sys/class/lego-port', 256 )
if ok:
	print 'lego-port folder:', ls
else:
	print 'ERROR: ev3_listdir'

ok, ls = ev3_listdir( '/sys/class/lego-sensor', 256 )
if ok:
	print 'lego-sensor folder:', ls
else:
	print 'ERROR: ev3_listdir'

ok, ls = ev3_listdir( '/sys/class/tacho-motor', 256 )
if ok:
	print 'tacho-motor folder:', ls
else:
	print 'ERROR: ev3_listdir'

ev3_uninit()
