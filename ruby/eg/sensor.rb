# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

color = [ '?', 'BLACK', 'BLUE', 'GREEN', 'YELLOW', 'RED', 'WHITE', 'BROWN' ]

def _check_pressed( sn )
  if sn == SENSOR__NONE_
    ok, val = ev3_read_keys()
    ( ok and (( val & EV3_KEY_UP ) != 0 ))
  else
    ok, val = get_sensor_value( 0, sn )
    ( ok and ( val != 0 ))
  end
end

if __FILE__ == $0
  puts 'Waiting the EV3 brick online...'
  if ev3_init() < 1 then exit( 1 ) end

  puts '*** ( EV3 ) Hello! ***'
  ev3_sensor_init()

  puts 'Found sensors:'
  SENSOR_DESC__LIMIT_.times do |i|
    type_inx = ev3_sensor_desc_type_inx( i )
    if type_inx != SENSOR_TYPE__NONE_
      _type = ev3_sensor_type( type_inx )
      puts "  type = #{_type}"
      port_name = ev3_sensor_port_name( i )
      puts "  port = #{port_name}"
      ok, mode = get_sensor_mode( i, 256 )
      if ok
        puts "  mode = #{mode}"
      end
      ok, n = get_sensor_num_values( i )
      if ok
        n.times do |ii|
          ok, val = get_sensor_value( ii, i )
          if ok
            puts "  value#{ii} = #{val}"
          end
        end
      end
    end
  end
  ok, sn_touch = ev3_search_sensor( LEGO_EV3_TOUCH )
  if ok
    puts 'TOUCH sensor is found, press BUTTON for EXIT...'
  else
    puts 'TOUCH sensor is NOT found, press UP on the EV3 brick for EXIT...'
  end
  ok, sn_color = ev3_search_sensor( LEGO_EV3_COLOR )
  if ok
    puts 'COLOR sensor is found, reading COLOR...'
    set_sensor_mode( sn_color, 'COL-COLOR' )
    loop do
      ok, val = get_sensor_value( 0, sn_color )
      if not ok or ( val < 0 ) or ( val >= color.length )
        val = 0
      end
      print "\r(#{color[ val ]})"
      $stdout.flush
      if _check_pressed( sn_touch ) then break end
      sleep( 0.2 )
      print "\r        \t"
      $stdout.flush
      if _check_pressed( sn_touch ) then break end
      sleep( 0.2 )
    end
  else
    puts 'COLOR sensor is NOT found'
    while not _check_pressed( sn_touch ) do
      sleep( 0.1 )
    end
  end
  ev3_uninit()
  puts
  puts '*** ( EV3 ) Bye! ***'
end
