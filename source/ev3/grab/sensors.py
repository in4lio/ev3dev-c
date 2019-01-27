# -*- coding: utf-8 -*-

#      ____ __     ____   ___    ____ __         (((((()
#     | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
#     |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
#                                                ((())))

__author__ = "Vitaly Kravtsov"
__author_email__ = "in4lio@gmail.com"
__copyright__ = "See the LICENSE file."

#pylint: skip-file

import urllib2
import json
import os

DIR     = os.path.dirname( os.path.realpath(__file__))
DICT    = os.path.join( DIR, 'sensors.yu' )
CACHE   = os.path.join( DIR, 'sensors.json' )

D_BEGIN = '($dict CLASS_TYPE\n(`CLASS_TYPE_NAME CLASS_TYPE_MODES CLASS_TYPE_COMMANDS)\n(`\n'
D_ROW   = '("{0}" ({1}) ({2}))\n'
D_END   = ')\n)'

def grab_sensors( url ):
    """
    Get sensor types, modes and commands from JSON file and make a dictionary
    with the following layout:

    ($dict CLASS_TYPE
        (` CLASS_TYPE_NAME  CLASS_TYPE_MODES  CLASS_TYPE_COMMANDS  )
        (`
        (  "sensor-name"    ( "mode" ... )    ( "command" ... )    )
        ...
        )
    )
    """
    if os.path.isfile( DICT ):
        return open( DICT, 'r' ).read()

#   -- cache the file from URL
    if not os.path.isfile( CACHE ):
        j = urllib2.urlopen( urllib2.Request(
            url,
            headers={ 'User-Agent': 'Mozilla/5.0', 'Content-Type': 'application/json' }
        ))
        with open( CACHE, 'wb' ) as f:
            f.write( j.read())

#   -- read the cached file
    with open( CACHE ) as f:
        data = json.load( f )

#   -- parse data
    result = D_BEGIN

    for sensor in data:
        if 'mode_info' in sensor:
            modes = ' '.join(( '"' + x[ 'name' ] + '"' for x in sensor[ 'mode_info' ]))
        else:
            modes = ''

        if 'cmd_info' in sensor:
            cmds = ' '.join(( '"' + x[ 'name' ] + '"' for x in sensor[ 'cmd_info' ]))
        else:
            cmds = ''

#       -- append the sensor only if it has any mode or command
        if modes or cmds:
            result += D_ROW.format( sensor[ 'name' ], modes, cmds )
            print sensor[ 'name' ]
        else:
            print '{0: <24}(ignored)'.format( sensor[ 'name' ])

    result += D_END

    with open( DICT, 'w' ) as f:
        f.write( result )

    return result

if __name__ == '__main__':
    grab_sensors( 'http://docs.ev3dev.org/projects/lego-linux-drivers/en/ev3dev-jessie/sensors.json' )
