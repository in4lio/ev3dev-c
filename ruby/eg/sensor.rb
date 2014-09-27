# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

color = [ '?', 'BLACK', 'BLUE', 'GREEN', 'YELLOW', 'RED', 'WHITE', 'BROWN' ]

def _touch_pressed( id )
  get_sensor_value( 0, id )[ 1 ] != 0
end

if __FILE__ == $0
  puts 'Waiting the EV3 brick online...'
  if ev3_init() < 1 then exit( 1 ) end

  puts '*** ( EV3 ) Hello! ***'
  ev3_sensor_init()

  puts 'Found sensors:'
  INPUT__COUNT_.times do |i|
    desc = ev3_get_sensor( i )
    if desc.connected
      puts "  port = in#{i + 1}"
      _type = ev3_sensor_type( desc.type_id )
      if _type
        puts "  type = #{_type}"
      else
        puts "  type_id = #{desc.type_id}"
      end
      ok, mode = get_sensor_mode( desc.id, 256 )
      if ok
        puts "  mode = #{mode}"
      end
      ok, n = get_sensor_num_values( desc.id )
      if ok
        n.times do |ii|
          ok, val = get_sensor_value( ii, desc.id )
          if ok
            puts "  value#{ii} = #{val}"
          end
        end
      end
    end
  end
  # Look for touch sensor
  p_touch = ev3_sensor_port( EV3_TOUCH )
  if p_touch != EV3_NONE
    puts 'EV3_TOUCH is found, press BUTTON for EXIT...'
    id_touch = ev3_get_sensor( p_touch ).id
    # Look for color sensor
    p_color = ev3_sensor_port( EV3_COLOR )
    if p_color != EV3_NONE
      id_color = ev3_get_sensor( p_color ).id
      puts 'EV3_COLOR is found, reading COLOR...'
      set_sensor_mode( id_color, 'COL-COLOR' )
      loop do
        # Read color sensor value
        ok, val = get_sensor_value( 0, id_color )
        if not ok or ( val < 0 ) or ( val >= color.length )
          val = 0
        end
        print "\r(#{color[ val ]})"
        $stdout.flush
        # Check touch pressed
        if _touch_pressed( id_touch ) then break end
        sleep( 0.2 )
        print "\r        \t"
        $stdout.flush
        if _touch_pressed( id_touch ) then break end
        sleep( 0.2 )
      end
    else
      puts 'EV3_COLOR is not found'
      # Wait touch pressed
      while not _touch_pressed( id_touch ) do
        sleep( 0.2 )
      end
    end
  else
    puts 'EV3_TOUCH is not found'
    exit( 0 )
  end
  ev3_uninit()
  puts
  puts '*** ( EV3 ) Bye! ***'
end
