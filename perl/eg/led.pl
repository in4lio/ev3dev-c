use lib "..";
use ev3;

print "Waiting the EV3 brick online...\n";
ev3::ev3_init() > 0 || exit( 1 );

my ( $ok, $state ) = ev3::get_led_brightness( $ev3::EV3_LEFT_RED );
if ( $ok ) {
    print "get_led_brightness( EV3_LEFT_RED ) = $state\n";
} else {
    print "ERROR: get_led_brightness()\n";
}
if ( !ev3::set_led_brightness( $ev3::EV3_LEFT_RED, 0 )) {
    print "ERROR: set_led_brightness()\n";
}
$state = ev3::get_led_trigger_inx( $ev3::EV3_RIGHT_RED );
print "get_led_trigger_inx( EV3_RIGHT_RED ) = $state\n";

if ( !ev3::set_led_trigger( $ev3::EV3_RIGHT_RED, "heartbeat" )) {
    print "ERROR: set_led_trigger()\n";
}
ev3::ev3_uninit();
