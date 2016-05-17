use lib "..";
use ev3;
use  Time::HiRes 'sleep';

if ( !$ev3::EV3_BRICK ) {
    # Disable auto-detection of the brick (you have to set the correct address below)
    $ev3::brick_addr = "192.168.0.204";
}
ev3::ev3_init() != -1 || exit( 1 );

if ( !$ev3::EV3_BRICK ) {
    print "The EV3 brick auto-detection is DISABLED,\nwaiting $ev3::brick_addr online with plugged tacho...\n";
} else {
    print "Waiting tacho is plugged...\n";
}
while ( ev3::ev3_tacho_init() < 1 ) {
    sleep( 1 );
}
print "*** ( EV3 ) Hello! ***\n";

print "Found tacho motors:\n";
for ( $i = 0; $i < $ev3::DESC_LIMIT; $i++ ) {
    my $type_inx = ev3::ev3_tacho_desc_type_inx( $i );
    if ( $type_inx != $ev3::TACHO_TYPE__NONE_) {
        my $port_type = ev3::ev3_tacho_type( $type_inx );
        print "  type = $port_type\n";
        my $port_name = ev3::ev3_tacho_port_name( $i );
        print "  port = $port_name\n";
    }
}
my ( $ok, $sn ) = ev3::ev3_search_tacho( $ev3::LEGO_EV3_M_MOTOR );
if ( $ok ) {
    print "LEGO_EV3_M_MOTOR is found, run for 5 sec...\n";
    ev3::set_tacho_stop_action_inx( $sn, $ev3::TACHO_COAST );
    ev3::set_tacho_duty_cycle_sp( $sn, 100 );
    ev3::set_tacho_time_sp( $sn, 5000 );
    ev3::set_tacho_ramp_up_sp( $sn, 2000 );
    ev3::set_tacho_ramp_down_sp( $sn, 2000 );
    ev3::set_tacho_command_inx( $sn, $ev3::TACHO_RUN_TIMED );
    # Wait tacho is stopped
    sleep( 0.1 );
    do {
        ( $ok, $flags ) = ev3::get_tacho_state_flags( $sn );
    } while ( $ok && $flags );

    printf( "run to relative position...\n" );
    ev3::set_tacho_duty_cycle_sp( $sn, 50 );
    ev3::set_tacho_ramp_up_sp( $sn, 0 );
    ev3::set_tacho_ramp_down_sp( $sn, 0 );
    ev3::set_tacho_position_sp( $sn, 90 );
    for ( $i = 0; $i < 8; $i++ ) {
        ev3::set_tacho_command_inx( $sn, $ev3::TACHO_RUN_TO_REL_POS );
        sleep( 0.5 );
    }
} else {
    print "LEGO_EV3_M_MOTOR is NOT found\n";
}
ev3::ev3_uninit();
print "*** ( EV3 ) Bye! ***\n";
