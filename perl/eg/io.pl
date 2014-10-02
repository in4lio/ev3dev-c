use lib "..";
use ev3;

ev3::ev3_init() > 0 || exit( 1 );

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
my ( $ok, $trig ) = ev3::ev3_read( "/sys/class/leds/ev3:red:right/trigger", 256 );
if ( $ok ) {
    print "$trig\n";
} else {
    print "ERROR: ev3_read_binary\n";
}
ev3::ev3_write( "/sys/class/leds/ev3:red:right/trigger", "heartbeat" );

ev3::ev3_uninit();
