# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

if ev3_init() < 1 then exit( 1 ) end

puts 'LEDs directory:'
ok, ls = ev3_listdir( '/sys/class/leds', 256 )
if ok
  puts ls
else
  puts 'ERROR: ev3_listdir'
end

ok, state = ev3_read_int( '/sys/class/leds/ev3:red:left/brightness' )
if ok
  ev3_write_bool( '/sys/class/leds/ev3:red:left/brightness', state == 0 )
else
  puts 'ERROR: ev3_write_bool'
end

puts 'ev3:red:right trigger:'
ok, trig = ev3_read( '/sys/class/leds/ev3:red:right/trigger', 256 )
if ok
  puts trig
else
  puts 'ERROR: ev3_read_binary'
end

ev3_write( '/sys/class/leds/ev3:red:right/trigger', 'heartbeat' )

puts 'EV3 ports state:'
for i in OUTPUT__BASE_ .. OUTPUT__BASE_ + OUTPUT__COUNT_ - 1
  ok, state = get_output_state( i, 256 )
  if ok
    port = ev3_output_name( i )
    puts "  #{port}: #{state}"
  else
    puts 'ERROR: get_output_state'
  end
end

for i in INPUT__BASE_ .. INPUT__BASE_ + INPUT__COUNT_ - 1
  ok, state = get_input_state( i, 256 )
  if ok
    port = ev3_input_name( i, EV3_PORT__NONE_ )
    puts "  #{port}: #{state}"
  else
    puts 'ERROR: get_input_state'
  end
end

ev3_uninit()
