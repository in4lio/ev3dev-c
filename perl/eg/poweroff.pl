use lib "..";
use ev3;

ev3::ev3_init() > 0 || exit( 1 );

print "Enter 'bye' to power-off the EV3 brick: ";
my $input = lc <STDIN>;
chomp $input;
if ( $input eq "bye" ) {
    ev3::ev3_poweroff();
    print "Goodbye!\n";
} else {
    print "Misspelling.\n";
}
ev3::ev3_uninit();
