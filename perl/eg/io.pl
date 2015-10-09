use lib "..";
use ev3;

ev3::ev3_init() > 0 || exit( 1 );

my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/leds", 256 );
if ( $ok ) {
    print "leds folder: $ls\n";
} else {
    print "ERROR: ev3_listdir( leds )\n";
}
my ( $ok, $state ) = ev3::ev3_read_int( "/sys/class/leds/ev3-left0:red:ev3dev/brightness" );
if ( $ok ) {
    if ( !ev3::ev3_write_int( "/sys/class/leds/ev3-left0:red:ev3dev/brightness", ( $state ? 0 : 255 ))) {
		print "ERROR: ev3_write_int( brightness )\n";
	}
} else {
    print "ERROR: ev3_read_int( brightness )\n";
}
my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/lego-port", 256 );
if ( $ok ) {
    print "lego-port folder: $ls\n";
} else {
    print "ERROR: ev3_listdir( lego-port )\n";
}
my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/lego-sensor", 256 );
if ( $ok ) {
    print "lego-sensor folder: $ls\n";
} else {
    print "ERROR: ev3_listdir( lego-sensor )\n";
}
my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/tacho-motor", 256 );
if ( $ok ) {
    print "tacho-motor folder: $ls\n";
} else {
    print "ERROR: ev3_listdir( tacho-motor )\n";
}

ev3::ev3_uninit();
