use lib "..";
use ev3;

if ( !$ev3::EV3_BRICK ) {
    # Disable auto-detection of the brick (you have to set the correct address below)
    $ev3::brick_addr = "192.168.0.204";
}
ev3::ev3_init() != $ev3::EV3_NONE || exit( 1 );

if ( !$ev3::EV3_BRICK ) {
    print "The EV3 brick auto-detection is DISABLED, waiting $ev3::brick_addr online...\n";
}
while ( ev3::ev3_tacho_init() == 0 ) {
    sleep( 1 );
}
print "*** ( EV3 ) Hello! ***\n";

print "Found tacho-motors:\n";
for ( $i = 0; $i < $ev3::OUTPUT__COUNT_; $i++ ) {
    if ( ev3::ev3_get_tacho_connected( $i )) {
        print "  port = out@{[$i + 1]}\n";
        my ( $ok, $type ) = ev3::get_tacho_type( ev3::ev3_get_tacho_id( $i ), 256 );
        if ( $ok ) {
            print "  type = $type\n";
        }
    }
}
# Look for minitacho motor
my $p = ev3::ev3_tacho_port( $ev3::MINITACHO );
if ( $p != $ev3::EV3_NONE ) {
    my $id = ev3::ev3_get_tacho_id( $p );

    print "MINITACHO is found, run for 5 sec...\n";
    ev3::set_tacho_regulation_mode( $id, "off" );
    ev3::set_tacho_run_mode( $id, "time" );
    ev3::set_tacho_stop_mode( $id, "brake" );
    ev3::set_tacho_duty_cycle_sp( $id, 100 );
    ev3::set_tacho_time_sp( $id, 5000 );
    ev3::set_tacho_ramp_up_sp( $id, 2000 );
    ev3::set_tacho_ramp_down_sp( $id, 2000 );
    ev3::set_tacho_run( $id, 1 );
} else {
    print "MINITACHO is not found\n";
}
ev3::ev3_uninit();
print "*** ( EV3 ) Bye! ***\n";
