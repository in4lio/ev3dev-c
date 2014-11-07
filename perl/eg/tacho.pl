use lib "..";
use ev3;

if ( !$ev3::EV3_BRICK ) {
    # Disable auto-detection of the brick (you have to set the correct address below)
    $ev3::brick_addr = "192.168.0.244";
}
ev3::ev3_init() != -1 || exit( 1 );

if ( !$ev3::EV3_BRICK ) {
    print "The EV3 brick auto-detection is DISABLED, waiting $ev3::brick_addr online...\n";
}
while ( ev3::ev3_tacho_init() < 1 ) {
    sleep( 1 );
}
print "*** ( EV3 ) Hello! ***\n";

print "Found tacho-motors:\n";
for ( $i = 0; $i < $ev3::TACHO_DESC__LIMIT_; $i++ ) {
    my $type_inx = ev3::ev3_tacho_desc_type_inx( $i );
    if ( $type_inx != $ev3::TACHO_TYPE__NONE_) {
        my $type = ev3::ev3_tacho_type( $type_inx );
        print "  type = $type\n";
        my $port_name = ev3::ev3_port_name( ev3::ev3_tacho_desc_port( $i ), ev3::ev3_tacho_desc_extport( $i ));
        print "  port = $port_name\n";
    }
}
my ( $ok, $sn ) = ev3::ev3_search_tacho( $ev3::MINITACHO );
if ( $ok ) {
    print "MINITACHO motor is found, run for 5 sec...\n";
    ev3::set_tacho_regulation_mode( $sn, "off" );
    ev3::set_tacho_run_mode( $sn, "time" );
    ev3::set_tacho_stop_mode( $sn, "brake" );
    ev3::set_tacho_duty_cycle_sp( $sn, 100 );
    ev3::set_tacho_time_sp( $sn, 5000 );
    ev3::set_tacho_ramp_up_sp( $sn, 2000 );
    ev3::set_tacho_ramp_down_sp( $sn, 2000 );
    ev3::set_tacho_run( $sn, 1 );
} else {
    print "MINITACHO motor is NOT found\n";
}
ev3::ev3_uninit();
print "*** ( EV3 ) Bye! ***\n";
