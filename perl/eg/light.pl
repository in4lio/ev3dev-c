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
Time::HiRes::sleep( 0.5 );
ev3::set_light( $ev3::LIT_LEFT, $ev3::LIT_RED );
ev3::set_light( $ev3::LIT_RIGHT, $ev3::LIT_RED );
Time::HiRes::sleep( 0.5 );
ev3::set_light( $ev3::LIT_LEFT, $ev3::LIT_AMBER );
ev3::set_light( $ev3::LIT_RIGHT, $ev3::LIT_AMBER );
Time::HiRes::sleep( 0.5 );
ev3::set_light( $ev3::LIT_LEFT, $ev3::LIT_GREEN );
ev3::set_light( $ev3::LIT_RIGHT, $ev3::LIT_GREEN );

ev3::ev3_uninit();
print "*** ( EV3 ) Bye! ***\n";
