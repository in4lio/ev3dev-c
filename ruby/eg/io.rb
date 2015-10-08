# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

if ev3_init() < 1 then exit( 1 ) end

ok, ls = ev3_listdir( '/sys/class/leds', 256 )
if ok
  puts "leds folder: #{ls}"
else
  puts 'ERROR: ev3_listdir( leds )'
end

ok, state = ev3_read_int( '/sys/class/leds/ev3-left0:red:ev3dev/brightness' )
if ok
  if not ev3_write_int( '/sys/class/leds/ev3-left0:red:ev3dev/brightness', state ? 0 : 255 )
			puts 'ERROR: ev3_write_int( brightness )'
  end
else
  puts 'ERROR: ev3_read_int'
end

ok, ls = ev3_listdir( '/sys/class/lego-port', 256 )
if ok
  puts "lego-port folder: #{ls}"
else
  puts 'ERROR: ev3_listdir( lego-port )'
end

ok, ls = ev3_listdir( '/sys/class/lego-sensor', 256 )
if ok
  puts "lego-sensor folder: #{ls}"
else
  puts 'ERROR: ev3_listdir( lego-sensor )'
end

ok, ls = ev3_listdir( '/sys/class/tacho-motor', 256 )
if ok
  puts "tacho-motor folder: #{ls}"
else
  puts 'ERROR: ev3_listdir( tacho-motor )'
end

ev3_uninit()
