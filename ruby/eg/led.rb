# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

puts 'Waiting the EV3 brick online...'
if ev3_init() < 1 then exit( 1 ) end

ok, state = get_led_brightness( EV3_RED_LEFT )
if ok
  puts "get_led_brightness( EV3_RED_LEFT ) = #{state}"
else
  puts 'ERROR: get_led_brightness'
end

if not set_led_brightness( EV3_RED_LEFT, 0 )
  puts 'ERROR: set_led_brightness'
end

state = get_led_trigger_inx( EV3_RED_RIGHT )
puts "get_led_trigger_inx( EV3_RED_RIGHT ) = #{state}"

if not set_led_trigger( EV3_RED_RIGHT, 'heartbeat' )
  puts 'ERROR: set_led_trigger'
end

ev3_uninit()
