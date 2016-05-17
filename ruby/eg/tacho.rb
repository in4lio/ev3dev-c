# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

if __FILE__ == $0
  puts "EV3_BRICK = #{EV3_BRICK}"

  if EV3_BRICK == 0
    # Disable auto-detection of the brick (you have to set the correct address below)
    Ev3.brick_addr = '192.168.0.204'
  end
  if ev3_init() == -1 then exit( 1 ) end

  if EV3_BRICK == 0
    puts 'The EV3 brick auto-detection is DISABLED,'
    puts "waiting #{Ev3.brick_addr} online with plugged tacho..."
  else
    puts 'Waiting tacho is plugged...'
  end
  $stdout.flush

  while ev3_tacho_init() < 1 do sleep( 1.0 ) end

  puts '*** ( EV3 ) Hello! ***'

  puts 'Found tacho motors:'
  DESC_LIMIT.times do |i|
    type_inx = ev3_tacho_desc_type_inx( i )
    if type_inx != TACHO_TYPE__NONE_
      _type = ev3_tacho_type( type_inx )
      puts "  type = #{_type}"
      _name = ev3_tacho_port_name( i )
      puts "  port = #{_name}"
    end
  end
  ok, sn = ev3_search_tacho( LEGO_EV3_M_MOTOR )
  if ok
    puts 'LEGO_EV3_M_MOTOR is found, run for 5 sec...'
    set_tacho_stop_action_inx( sn, TACHO_COAST )
    set_tacho_speed_sp( sn, 1000 )
    set_tacho_time_sp( sn, 5000 )
    set_tacho_ramp_up_sp( sn, 2000 )
    set_tacho_ramp_down_sp( sn, 2000 )
    set_tacho_command_inx( sn, TACHO_RUN_TIMED )
    # Wait tacho is stopped
    sleep( 0.1 )
    ok, flags = get_tacho_state_flags( sn )
    while ok and ( flags != 0 ) do
      ok, flags = get_tacho_state_flags( sn )
    end
    puts 'run to relative position...'
    set_tacho_speed_sp( sn, 500 )
    set_tacho_ramp_up_sp( sn, 0 )
    set_tacho_ramp_down_sp( sn, 0 )
    set_tacho_position_sp( sn, 90 )
    8.times do |i|
      set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS )
      sleep( 0.5 )
    end
  else
    puts 'LEGO_EV3_M_MOTOR is NOT found'
  end
  ev3_uninit()
  puts '*** ( EV3 ) Bye! ***'
end
