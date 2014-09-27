# -*- coding: utf-8 -*-

#FIXME: not the best way to import the library
$LOAD_PATH << if ENV[ 'OS' ] == 'Windows_NT' then '../mingw' else '..' end
require 'ev3'
include Ev3

if ev3_init() < 1 then exit( 1 ) end

print 'Enter \'bye\' to power-off the EV3 brick: '
$stdout.flush
if gets.chomp.casecmp( 'bye' ) == 0
	ev3_poweroff()
	puts 'Goodbye!'
else
	puts 'Misspelling.'
end

ev3_uninit()
