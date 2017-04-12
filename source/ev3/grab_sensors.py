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

F_SENSOR_JSON = 'sensors.json'

D_BEGIN = '($dict CLASS_TYPE\n(`CLASS_TYPE_NAME CLASS_TYPE_MODES CLASS_TYPE_COMMANDS)\n(`\n'
D_ROW   = '("{0}" ({1}) ({2}))\n'
D_END   = ')\n)'

def grab_sensors( url, cache = None ):
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
    if isinstance( cache, basestring ):
        if not cache:
            cache = F_SENSOR_JSON
#       -- cache the file from URL if it doesn't exist
        if not os.path.isfile( cache ):
            j = urllib2.urlopen( url )
            with open( cache, 'wb' ) as f:
                f.write( j.read())
#       -- read the cached file
        with open( cache ) as f:
            data = json.load( f )
    else:
#       -- read data directly
        data = json.load( urllib2.urlopen( url ))

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
    return result

if __name__ == '__main__':
#   -- test
    with open( 'sensors.yu', 'w' ) as f:
        f.write( grab_sensors( 'http://docs.ev3dev.org/projects/lego-linux-drivers/en/ev3dev-jessie/sensors.json' ))
