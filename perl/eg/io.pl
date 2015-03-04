use lib "..";
use ev3;

ev3::ev3_init() > 0 || exit( 1 );

my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/leds", 256 );
if ( $ok ) {
    print "leds folder: $ls\n";
} else {
    print "ERROR: ev3_listdir\n";
}
my ( $ok, $state ) = ev3::ev3_read_int( "/sys/class/leds/ev3:red:left/brightness" );
if ( $ok ) {
    ev3::ev3_write_int( "/sys/class/leds/ev3:red:left/brightness", ( $state ? 0 : 255 ));
} else {
    print "ERROR: ev3_read_int\n";
}
my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/lego-port", 256 );
if ( $ok ) {
    print "lego-port folder: $ls\n";
} else {
    print "ERROR: ev3_listdir\n";
}
my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/lego-sensor", 256 );
if ( $ok ) {
    print "lego-sensor folder: $ls\n";
} else {
    print "ERROR: ev3_listdir\n";
}
my ( $ok, $ls ) = ev3::ev3_listdir( "/sys/class/tacho-motor", 256 );
if ( $ok ) {
    print "tacho-motor folder: $ls\n";
} else {
    print "ERROR: ev3_listdir\n";
}

ev3::ev3_uninit();
