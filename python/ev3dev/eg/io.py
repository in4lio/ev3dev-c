# -*- coding: utf-8 -*-
#pylint: skip-file

import sys
from ev3dev import *

if ev3_init() < 1: sys.exit( 1 )

print 'LEDs directory:'
ok, ls = ev3_listdir( '/sys/class/leds', 256 )
print ls if ok else 'ERROR: ev3_listdir'

ok, state = ev3_read_int( '/sys/class/leds/ev3:red:left/brightness' )
if ok:
    ev3_write_bool( '/sys/class/leds/ev3:red:left/brightness', not state )
else:
    print 'ERROR: ev3_write_bool'

print 'ev3:red:right trigger:'
ok, trig = ev3_read( '/sys/class/leds/ev3:red:right/trigger', 256 )
print trig if ok else 'ERROR: ev3_read_binary'

ev3_write( '/sys/class/leds/ev3:red:right/trigger', 'heartbeat' )

print 'EV3 ports state:'
for i in range( OUTPUT__BASE_, OUTPUT__BASE_ + OUTPUT__COUNT_ ):
	ok, state = get_output_state( i, 256 )
	if ok:
		print '  %s: %s' % ( ev3_output_name( i ), state )
	else:
		print 'ERROR: get_output_state'

for i in range( INPUT__BASE_, INPUT__BASE_ + INPUT__COUNT_ ):
	ok, state = get_input_state( i, 256 )
	if ok:
		print '  %s: %s' % ( ev3_input_name( i, EV3_PORT__NONE_ ), state )
	else:
		print 'ERROR: get_input_state'

ev3_uninit()
