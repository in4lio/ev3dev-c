## Examples in C

Name                                                                  | Description
:---:                                                                 | :---
[dc](http://in4lio.github.io/ev3dev-c/dc_8c-example.html)             | use of a DC motor
[drive](http://in4lio.github.io/ev3dev-c/drive_8c-example.html)       | a comprehensive example based on coroutines
[io](http://in4lio.github.io/ev3dev-c/io_8c-example.html)             | using low-level functions
[light](http://in4lio.github.io/ev3dev-c/light_8c-example.html)       | LEDs blinking example
[port](http://in4lio.github.io/ev3dev-c/port_8c-example.html)         | use of EV3 ports
[poweroff](http://in4lio.github.io/ev3dev-c/poweroff_8c-example.html) | turn the brick off remotely
[rcx_led](http://in4lio.github.io/ev3dev-c/rcx_led_8c-example.html)   | use of a RCX LED
[remote](http://in4lio.github.io/ev3dev-c/remote_8c-example.html)     | an IR remote control using "brick" simplified library
[sensor](http://in4lio.github.io/ev3dev-c/sensor_8c-example.html)     | TOUCH and COLOR sensors example
[servo](http://in4lio.github.io/ev3dev-c/servo_8c-example.html)       | a SERVO motor example
[tacho](http://in4lio.github.io/ev3dev-c/tacho_8c-example.html)       | a TACHO motor running for 5 sec
[tacho_cpp](http://in4lio.github.io/ev3dev-c/tacho_8cpp-example.html) | a TACHO motor example in C++

## How to make examples?

```
> cd remote/
> make
```

Makefile targets                       | Description
:---                                   | :---
`release`                              | BUILD example using precompiled "ev3dev-c" library
`release-clean`                        | REMOVE files created during building `release` target
`debug` (default)                      | BUILD example using the source files of "ev3dev-c" library
`debug-clean` or `clean`               | REMOVE all files created during building `debug` target
`debug-clean-binary` or `clean-binary` | REMOVE only binary files created during building `debug` target

## See also

[Examples in Python](../python/ev3dev/eg)<br>
[Examples in Perl](../perl/eg)<br>
[Examples in Ruby](../ruby/eg)
