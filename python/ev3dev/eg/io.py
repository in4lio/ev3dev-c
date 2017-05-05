# -*- coding: utf-8 -*-

import sys
from ev3dev import *

if ev3_init() < 1: sys.exit( 1 )

ok, ls = ev3_listdir( '/sys/class/leds', 256 )
if ok:
	print 'leds folder:', ls
else:
	print 'ERROR: ev3_listdir( leds )'

ok, state = ev3_read_int( '/sys/class/leds/ev3:left:red:ev3dev/brightness' )
if ok:
    if not ev3_write_int( '/sys/class/leds/ev3:left:red:ev3dev/brightness', 0 if state else 255 ):
			print 'ERROR: ev3_write_int( brightness )'
else:
    print 'ERROR: ev3_read_int( brightness )'

ok, ls = ev3_listdir( '/sys/class/lego-port', 256 )
if ok:
	print 'lego-port folder:', ls
else:
	print 'ERROR: ev3_listdir( lego-port )'

ok, ls = ev3_listdir( '/sys/class/lego-sensor', 256 )
if ok:
	print 'lego-sensor folder:', ls
else:
	print 'ERROR: ev3_listdir( lego-sensor )'

ok, ls = ev3_listdir( '/sys/class/tacho-motor', 256 )
if ok:
	print 'tacho-motor folder:', ls
else:
	print 'ERROR: ev3_listdir( tacho-motor )'

ev3_uninit()
