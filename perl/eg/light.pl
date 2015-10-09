use Time::HiRes;
use lib "..";
use ev3;

print "Waiting the EV3 brick online...\n";
ev3::ev3_init() > 0 || exit( 1 );

print "*** ( EV3 ) Hello! ***\n";

ev3::set_light_blink( $ev3::LIT_RIGHT, $ev3::LIT_GREEN, 1000, 500 );
Time::HiRes::sleep( 0.5 );
ev3::set_light_blink( $ev3::LIT_RIGHT, $ev3::LIT_RED, 1000, 500 );

ev3::set_light_blink( $ev3::LIT_LEFT, $ev3::LIT_GREEN, 1000, 1000 );
Time::HiRes::sleep( 1.5 );
ev3::set_light_blink( $ev3::LIT_LEFT, $ev3::LIT_RED, 1000, 1000 );
Time::HiRes::sleep( 7.5 );

ev3::set_light( $ev3::LIT_LEFT, $ev3::LIT_OFF );
ev3::set_light( $ev3::LIT_RIGHT, $ev3::LIT_OFF );
my $col = ev3::light_color( ev3::get_light( $ev3::LIT_LEFT ));
print "LEFT : $col\n";
$col = ev3::light_color( ev3::get_light( $ev3::LIT_RIGHT ));
print "RIGHT: $col\n";
Time::HiRes::sleep( 0.5 );
ev3::set_light( $ev3::LIT_LEFT, $ev3::LIT_RED );
ev3::set_light( $ev3::LIT_RIGHT, $ev3::LIT_RED );
$col = ev3::light_color( ev3::get_light( $ev3::LIT_LEFT ));
print "LEFT : $col\n";
$col = ev3::light_color( ev3::get_light( $ev3::LIT_RIGHT ));
print "RIGHT: $col\n";
Time::HiRes::sleep( 0.5 );
ev3::set_light( $ev3::LIT_LEFT, $ev3::LIT_AMBER );
ev3::set_light( $ev3::LIT_RIGHT, $ev3::LIT_AMBER );
$col = ev3::light_color( ev3::get_light( $ev3::LIT_LEFT ));
print "LEFT : $col\n";
$col = ev3::light_color( ev3::get_light( $ev3::LIT_RIGHT ));
print "RIGHT: $col\n";
Time::HiRes::sleep( 0.5 );
ev3::set_light( $ev3::LIT_LEFT, $ev3::LIT_GREEN );
ev3::set_light( $ev3::LIT_RIGHT, $ev3::LIT_GREEN );
$col = ev3::light_color( ev3::get_light( $ev3::LIT_LEFT ));
print "LEFT : $col\n";
$col = ev3::light_color( ev3::get_light( $ev3::LIT_RIGHT ));
print "RIGHT: $col\n";

ev3::ev3_uninit();
print "*** ( EV3 ) Bye! ***\n";
