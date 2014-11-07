use lib "..";
use ev3;

ev3::ev3_init() > 0 || exit( 1 );

print "LEDs directory:\n";
my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/leds", 256 );
if ( $ok ) {
    print "$ls\n";
} else {
    print "ERROR: ev3_listdir\n";
}
my ( $ok, $state ) = ev3::ev3_read_int( "/sys/class/leds/ev3:red:left/brightness" );
if ( $ok ) {
    ev3::ev3_write_bool( "/sys/class/leds/ev3:red:left/brightness", !$state );
} else {
    print "ERROR: ev3_write_bool\n";
}
print "ev3:red:right trigger:\n";
my ( $ok, $trig ) = ev3::ev3_read( "/sys/class/leds/ev3:red:right/trigger", 256 );
if ( $ok ) {
    print "$trig\n";
} else {
    print "ERROR: ev3_read_binary\n";
}
ev3::ev3_write( "/sys/class/leds/ev3:red:right/trigger", "heartbeat" );

print "EV3 ports state:\n";
for ( $i = $ev3::OUTPUT__BASE_; $i < $ev3::OUTPUT__BASE_ + $ev3::OUTPUT__COUNT_; $i++ ) {
	my ( $ok, $state ) = ev3::get_output_state( $i, 256 );
	if ( $ok ) {
		my $port = ev3::ev3_output_name( $i );
		print "  $port: $state\n";
	} else {
		print "ERROR: get_output_state\n";
	}
}
for ( $i = $ev3::INPUT__BASE_; $i < $ev3::INPUT__BASE_ + $ev3::INPUT__COUNT_; $i++ ) {
	my ( $ok, $state ) = ev3::get_input_state( $i, 256 );
	if ( $ok ) {
		my $port = ev3::ev3_input_name( $i, $ev3::EV3_PORT__NONE_ );
		print "  $port: $state\n";
	} else {
		print "ERROR: get_input_state\n";
	}
}
ev3::ev3_uninit();
