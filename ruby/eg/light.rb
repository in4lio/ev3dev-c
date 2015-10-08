# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

puts 'Waiting the EV3 brick online...'
if ev3_init() < 1 then exit( 1 ) end

puts '*** ( EV3 ) Hello! ***'

set_light_blink( LIT_RIGHT, LIT_GREEN, 1000, 500 )
sleep( 0.5 )
set_light_blink( LIT_RIGHT, LIT_RED, 1000, 500 )

set_light_blink( LIT_LEFT, LIT_GREEN, 1000, 1000 )
sleep( 1.5 )
set_light_blink( LIT_LEFT, LIT_RED, 1000, 1000 )
sleep( 7.5 )

set_light( LIT_LEFT, LIT_OFF )
set_light( LIT_RIGHT, LIT_OFF )
col = light_color( get_light( LIT_LEFT ))
puts "LEFT : #{col}"
col = light_color( get_light( LIT_RIGHT ))
puts "RIGHT: #{col}"
sleep( 0.5 )
set_light( LIT_LEFT, LIT_RED )
set_light( LIT_RIGHT, LIT_RED )
col = light_color( get_light( LIT_LEFT ))
puts "LEFT : #{col}"
col = light_color( get_light( LIT_RIGHT ))
puts "RIGHT: #{col}"
sleep( 0.5 )
set_light( LIT_LEFT, LIT_AMBER )
set_light( LIT_RIGHT, LIT_AMBER )
col = light_color( get_light( LIT_LEFT ))
puts "LEFT : #{col}"
col = light_color( get_light( LIT_RIGHT ))
puts "RIGHT: #{col}"
sleep( 0.5 )
set_light( LIT_LEFT, LIT_GREEN )
set_light( LIT_RIGHT, LIT_GREEN )
col = light_color( get_light( LIT_LEFT ))
puts "LEFT : #{col}"
col = light_color( get_light( LIT_RIGHT ))
puts "RIGHT: #{col}"

ev3_uninit()
puts '*** ( EV3 ) Bye! ***'
