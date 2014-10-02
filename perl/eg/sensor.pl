use Time::HiRes;
use lib "..";
use ev3;

my @color = ( "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" );

sub _touch_pressed {
    my $id = shift;
    return ( ev3::get_sensor_value( 0, $id ))[ 1 ] != 0;
}

print "Waiting the EV3 brick online...\n";
ev3::ev3_init() > 0 || exit( 1 );

print "*** ( EV3 ) Hello! ***\n";
ev3::ev3_sensor_init();

print "Found sensors:\n";
for ( $i = 0; $i < $ev3::INPUT__COUNT_; $i++ ) {
    if ( ev3::ev3_get_sensor_connected( $i )) {
        print "  port = in@{[$i + 1]}\n";
        my $type_id = ev3::ev3_get_sensor_type_id( $i );
        my $type = ev3::ev3_sensor_type( $type_id );
        if ( $type ) {
            print "  type = $type\n";
        } else {
            print "  type_id = $type_id\n";
        }
        my ( $ok, $mode ) = ev3::get_sensor_mode( ev3::ev3_get_sensor_id( $i ), 256 );
        if ( $ok ) {
            print "  mode = $mode\n";
        }
        my ( $ok, $n ) = ev3::get_sensor_num_values( ev3::ev3_get_sensor_id( $i ));
        if ( $ok ) {
            for ( $ii = 0; $ii < $n; $ii++ ) {
                my ( $ok, $val ) = ev3::get_sensor_value( $ii, ev3::ev3_get_sensor_id( $i ));
                if ( $ok ) {
                    print "  value$ii = $val\n";
                }
            }
        }
    }
}
# Look for touch sensor
my $p_touch = ev3::ev3_sensor_port( $ev3::EV3_TOUCH );
if ( $p_touch != $ev3::EV3_NONE ) {
    print "EV3_TOUCH is found, press BUTTON for EXIT...\n";
    my $id_touch = ev3::ev3_get_sensor_id( $p_touch );
    # Look for color sensor
    my $p_color = ev3::ev3_sensor_port( $ev3::EV3_COLOR );
    if ( $p_color != $ev3::EV3_NONE ) {
        my $id_color = ev3::ev3_get_sensor_id( $p_color );
        print "EV3_COLOR is found, reading COLOR...\n";
        ev3::set_sensor_mode( $id_color, "COL-COLOR" );
        while ( true ) {
            # Read color sensor value
            my ( $ok, $val ) = ev3::get_sensor_value( 0, $id_color );
            if ( !$ok || ( $val < 0 ) || ( $val >= scalar @color )) {
                $val = 0;
            }
            print "\r($color[ $val ])";
            $| = 1;
            # Check touch pressed
            if ( _touch_pressed( $id_touch )) {
                last;
            }
            Time::HiRes::sleep( 0.2 );
            print "\r        ";
            $| = 1;
            if ( _touch_pressed( $id_touch )) {
                last;
            }
            Time::HiRes::sleep( 0.2 );
        }
    } else {
        print "EV3_COLOR is not found\n";
        # Wait touch pressed
        while ( !_touch_pressed( $id_touch )) {
            Time::HiRes::sleep( 0.2 );
        }
    }
} else {
    print "EV3_TOUCH is not found\n";
}
ev3::ev3_uninit();
print "\n*** ( EV3 ) Bye! ***\n";
