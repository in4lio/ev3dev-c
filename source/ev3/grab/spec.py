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
import urlparse

#   ---------------------------------------------------------------------------
DIR = os.path.dirname( os.path.realpath(__file__))

F_SENSOR_DICT  = os.path.join( DIR, 'sensors.yu' )
F_PORT_DICT    = os.path.join( DIR, 'ports.yu' )

D_SENSOR_BEGIN = '($dict CLASS_TYPE\n(`CLASS_TYPE_NAME CLASS_TYPE_MODES CLASS_TYPE_COMMANDS)\n(`\n'
D_SENSOR_ROW   = '("{0}" ({1}) ({2}))\n'
D_SENSOR_END   = ')\n)'

D_PORT_BEGIN   = '($dict CLASS_TYPE\n(`CLASS_TYPE_NAME CLASS_TYPE_MODES)\n(`\n'
D_PORT_ROW     = '("{0}" ({1}))\n'
D_PORT_END     = ')\n)'

#   ---------------------------------------------------------------------------
def cache_json( url, force=False ):
    """
    Cache a JSON file.
    """
    cache = os.path.join( DIR, os.path.basename( urlparse.urlparse( url ).path ))

    if force or not os.path.isfile( cache ):
        j = urllib2.urlopen( urllib2.Request(
            url,
            headers={ 'User-Agent': 'Mozilla/5.0', 'Content-Type': 'application/json' }
        ))
        with open( cache, 'wb' ) as f:
            f.write( j.read())

    return cache

#   ---------------------------------------------------------------------------
def grab_sensors( url, force=False ):
    """
    Get data of sensors from the specification and make a dictionary
    with the following layout:

    ($dict CLASS_TYPE
        (` CLASS_TYPE_NAME  CLASS_TYPE_MODES  CLASS_TYPE_COMMANDS  )
        (`
        (  "sensor-name"    ( "mode" ... )    ( "command" ... )    )
        ...
        )
    )
    """
    if not force and os.path.isfile( F_SENSOR_DICT ):
        return open( F_SENSOR_DICT, 'r' ).read()

#   -- read the cached file
    with open( cache_json( url )) as f:
        data = json.load( f )

#   -- parse data
    result = D_SENSOR_BEGIN

    for sensor in data:
        if 'mode_info' in sensor:
            modes = ' '.join( '"' + x[ 'name' ] + '"' for x in sensor[ 'mode_info' ])
        else:
            modes = ''

        if 'cmd_info' in sensor:
            cmds = ' '.join( '"' + x[ 'name' ] + '"' for x in sensor[ 'cmd_info' ])
        else:
            cmds = ''

#       -- append the sensor only if it has any mode or command
        if modes or cmds:
            result += D_SENSOR_ROW.format( sensor[ 'name' ], modes, cmds )
            print sensor[ 'name' ]
        else:
            print '{0: <24}(ignored)'.format( sensor[ 'name' ])

    result += D_SENSOR_END

    with open( F_SENSOR_DICT, 'w' ) as f:
        f.write( result )

    return result

#   ---------------------------------------------------------------------------
def grab_ports( url, force=False ):
    """
    Get data of ports from the specification and make a dictionary
    with the following layout:

    ($dict CLASS_TYPE
        (` CLASS_TYPE_NAME  CLASS_TYPE_MODES  )
        (`
        (  "port-name"      ( "mode" ... )    )
        ...
        )
    )
    """

    if not force and os.path.isfile( F_PORT_DICT ):
        return open( F_PORT_DICT, 'r' ).read()

#   -- read the cached file
    with open( cache_json( url, force )) as f:
        data = json.load( f )

#   -- parse data
    result = D_PORT_BEGIN

    for k in data:
        port = data[ k ]
        if 'mode_info' in port:
            modes = ' '.join( '"' + x[ 'name' ] + '"' for x in port[ 'mode_info' ])
        else:
            modes = ''

        result += D_PORT_ROW.format( port[ 'name' ], modes )
        print port[ 'name' ]

    result += D_PORT_END

    with open( F_PORT_DICT, 'w' ) as f:
        f.write( result )

    return result

#   ---------------------------------------------------------------------------
if __name__ == '__main__':
#   -- test
    grab_sensors(
    'http://docs.ev3dev.org/projects/lego-linux-drivers/en/ev3dev-stretch/sensors.json', force=True )
    grab_ports(
    'http://docs.ev3dev.org/projects/lego-linux-drivers/en/ev3dev-stretch/ports.json', force=True )
