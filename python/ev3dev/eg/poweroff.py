# -*- coding: utf-8 -*-

import sys
from ev3dev import *

if ev3_init() < 1: sys.exit( 1 )

if raw_input( 'Enter \'bye\' to power-off the EV3 brick: ' ).lower() == 'bye' :
	ev3_poweroff()
	print 'Goodbye!'
else:
	print 'Misspelling.'

ev3_uninit()
