# -*- coding: utf-8 -*-

from time import sleep
import sys
from ev3dev import *

print 'Waiting the EV3 brick online...'
if ev3_init() < 1: sys.exit( 1 )

print '*** ( EV3 ) Hello! ***'

set_light_blink( LIT_RIGHT, LIT_GREEN, 1000, 500 )
sleep( 0.5 )
set_light_blink( LIT_RIGHT, LIT_RED, 1000, 500 )

set_light_blink( LIT_LEFT, LIT_GREEN, 1000, 1000 )
sleep( 1.5 )
set_light_blink( LIT_LEFT, LIT_RED, 1000, 1000 )
sleep( 7.5 )

set_light( LIT_LEFT, LIT_OFF )
set_light( LIT_RIGHT, LIT_OFF )
sleep( 0.5 )
set_light( LIT_LEFT, LIT_RED )
set_light( LIT_RIGHT, LIT_RED )
sleep( 0.5 )
set_light( LIT_LEFT, LIT_AMBER )
set_light( LIT_RIGHT, LIT_AMBER )
sleep( 0.5 )
set_light( LIT_LEFT, LIT_GREEN )
set_light( LIT_RIGHT, LIT_GREEN )

ev3_uninit()
print '*** ( EV3 ) Bye! ***'
