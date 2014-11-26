#pylint: skip-file

import urllib2
import json
import os

F_SENSOR_JSON = '../sensors.json'

BEGIN = """($dict CLASS_TYPE
	(` {0: <{1}}  CLASS_TYPE_MODES  CLASS_TYPE_COMMANDS )
	(`
"""
COL_1 = 'CLASS_TYPE_NAME'
ROW = """	(  {0: <{1}}  (`{2})  (`{3}))
"""
END = """	)
)
"""

"""
Get sensor types, modes and commands from JSON file and make a dictionary with the following layout:
($dict CLASS_TYPE
    (` CLASS_TYPE_NAME  CLASS_TYPE_MODES  CLASS_TYPE_COMMANDS )
    (`
    (  "sensor-name"    (` "sensor-mode" ... )  (` "sensor-command" ... ))
    ...
    )
)
"""
def grab_sensors( url ):
#   -- get the file from URL if it has not been read yet
    if not os.path.isfile( F_SENSOR_JSON ):
        j = urllib2.urlopen( url )
        with open( F_SENSOR_JSON, 'wb' ) as f:
            f.write( j.read())

#   -- parse file
    with open( F_SENSOR_JSON ) as f:
        data = json.load( f )

    l_name = len( max([ x[ 'name' ] for x in data ], key = len )) + 2  # ""

    result = BEGIN.format( COL_1, l_name )

    for sensor in data:
        name = '"%s"' % ( sensor[ 'name' ])

        modelist = ''
        try:
            for mode in sensor[ 'ms_mode_info' ]:
                modelist += '"%s" ' % ( mode[ 'name' ])
        except KeyError:
            pass

        if modelist:
            modelist = ' ' + modelist

        cmdlist = ''
        try:
            for cmd in sensor[ 'ms_cmd_info' ]:
                cmdlist += '"%s" ' % ( cmd[ 'name' ])
        except KeyError:
            pass

        if cmdlist:
            cmdlist = ' ' + cmdlist

        if modelist or cmdlist:
#           -- append the sensor only if it has any mode or command
            print sensor[ 'name' ]
            result += ROW.format( name, l_name, modelist, cmdlist )
        else:
            print '{0: <{1}}(ignored)'.format( sensor[ 'name' ], l_name )

    result += END
    return result

if __name__ == '__main__':
    with open( './sensors.yu', 'w' ) as f:
        f.write( grab_sensor_type_dict( 'https://raw.githubusercontent.com/ev3dev/ev3dev.github.io/master/_data/sensors.json' ))
