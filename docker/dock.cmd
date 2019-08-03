set cl =/bin/bash
if not "%1"=="" set cl=%*

docker run --rm -it -h ev3dev -v "%cd%":/home/robot/ev3dev-c -w /home/robot/ev3dev-c ev3cc %cl%
