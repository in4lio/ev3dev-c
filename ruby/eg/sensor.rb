# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

color = [ '?', 'BLACK', 'BLUE', 'GREEN', 'YELLOW', 'RED', 'WHITE', 'BROWN' ]

def _touch_pressed( sn )
  get_sensor_value( 0, sn )[ 1 ] != 0
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
      port_name = ev3_port_name( ev3_sensor_desc_port( i ), ev3_sensor_desc_extport( i ))
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
    ok, sn_color = ev3_search_sensor( EV3_UART_29 )
    if ok
      puts 'COLOR sensor is found, reading COLOR...'
      set_sensor_mode( sn_color, 'COL-COLOR' )
      loop do
        # Read color sensor value
        ok, val = get_sensor_value( 0, sn_color )
        if not ok or ( val < 0 ) or ( val >= color.length )
          val = 0
        end
        print "\r(#{color[ val ]})"
        $stdout.flush
        # Check touch pressed
        if _touch_pressed( sn_touch ) then break end
        sleep( 0.2 )
        print "\r        \t"
        $stdout.flush
        if _touch_pressed( sn_touch ) then break end
        sleep( 0.2 )
      end
    else
      puts 'COLOR sensor is NOT found'
      # Wait touch pressed
      while not _touch_pressed( sn_touch ) do
        sleep( 0.2 )
      end
    end
  else
    puts 'TOUCH sensor is NOT found'
    exit( 0 )
  end
  ev3_uninit()
  puts
  puts '*** ( EV3 ) Bye! ***'
end
