use lib "..";
use ev3;

ev3::ev3_init() > 0 || exit( 1 );

my ( $ok, $state ) = ev3::get_led_brightness( $ev3::EV3_RED_LEFT );
if ( $ok ) {
    print "get_led_brightness( EV3_RED_LEFT ) = $state\n";
} else {
    print "ERROR: get_led_brightness\n";
}
if ( !ev3::set_led_brightness( $ev3::EV3_RED_LEFT, 0 )) {
    print "ERROR: set_led_brightness\n";
}
$state = ev3::get_led_trigger_inx( $ev3::EV3_RED_RIGHT );
print "get_led_trigger_inx( EV3_RED_RIGHT ) = $state\n";

if ( !ev3::set_led_trigger( $ev3::EV3_RED_RIGHT, "heartbeat" )) {
    print "ERROR: set_led_trigger\n";
}
ev3::ev3_uninit();
