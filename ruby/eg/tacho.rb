# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

if __FILE__ == $0
  if not EV3_BRICK
    # Disable auto-detection of the brick (you have to set the correct address below)
    Ev3.brick_addr = '192.168.0.204'
  end
  if ev3_init() == EV3_NONE then exit( 1 ) end

  if not EV3_BRICK
    puts "The EV3 brick auto-detection is DISABLED, waiting #{ev3.brick_addr} online..."
  end

  while ev3_tacho_init() == 0 do sleep( 1.0 ) end

  puts '*** ( EV3 ) Hello! ***'

  puts 'Found tacho-motors:'
  OUTPUT__COUNT_.times do |i|
    if ev3_get_tacho_connected( i )
      puts "  port = out#{i + 1}"
      ok, _type = get_tacho_type( ev3_get_tacho_id( i ), 256 )
      if ok
        puts "  type = #{_type}"
      end
    end
  end
  # Look for minitacho motor
  p = ev3_tacho_port( MINITACHO )
  if p != EV3_NONE
    _id = ev3_get_tacho_id( p )

    puts 'MINITACHO is found, run for 5 sec...'
    set_tacho_regulation_mode( _id, 'off' )
    set_tacho_run_mode( _id, 'time' )
    set_tacho_stop_mode( _id, 'brake' )
    set_tacho_duty_cycle_sp( _id, 100 )
    set_tacho_time_sp( _id, 5000 )
    set_tacho_ramp_up_sp( _id, 2000 )
    set_tacho_ramp_down_sp( _id, 2000 )
    set_tacho_run( _id, true )
  else
    puts 'MINITACHO is not found'
  end
  ev3_uninit()
  puts '*** ( EV3 ) Bye! ***'
end
