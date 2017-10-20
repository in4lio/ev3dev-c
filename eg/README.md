### Examples in C

Name           | Description
:---:          | :---
[dc.c]         | Use of a DC motor
[drive.c]      | Comprehensive example based on coroutines
[io.c]         | Use of low-level functions
[hello.c]      | "Hello world"
[light.c]      | LEDs blinking example
[port.c]       | Use of EV3 ports
[poweroff.c]   | Turn off the EV3 brick remotely
[rcx_led.c]    | Use of a RCX LED
[remote.c]     | IR remote control using "brick" simplified library
[sensor.c]     | TOUCH and COLOR sensors example
[servo.c]      | SERVO motor example
[tacho.c]      | TACHO motor running for 5 sec
[tacho.cpp]    | TACHO motor example in C++

[dc.c]:          http://in4lio.github.io/ev3dev-c/dc_8c-example.html
[drive.c]:       http://in4lio.github.io/ev3dev-c/drive_8c-example.html
[io.c]:          http://in4lio.github.io/ev3dev-c/io_8c-example.html
[hello.c]:       http://in4lio.github.io/ev3dev-c/hello_8c-example.html
[light.c]:       http://in4lio.github.io/ev3dev-c/light_8c-example.html
[port.c]:        http://in4lio.github.io/ev3dev-c/port_8c-example.html
[poweroff.c]:    http://in4lio.github.io/ev3dev-c/poweroff_8c-example.html
[rcx_led.c]:     http://in4lio.github.io/ev3dev-c/rcx_led_8c-example.html
[remote.c]:      http://in4lio.github.io/ev3dev-c/remote_8c-example.html
[sensor.c]:      http://in4lio.github.io/ev3dev-c/sensor_8c-example.html
[servo.c]:       http://in4lio.github.io/ev3dev-c/servo_8c-example.html
[tacho.c]:       http://in4lio.github.io/ev3dev-c/tacho_8c-example.html
[tacho.cpp]:     http://in4lio.github.io/ev3dev-c/tacho_8cpp-example.html

### How to make an example

    cd ev3dev-c/eg/remote/
    make <target>

Makefile targets                       | Description
:---                                   | :---
`release`                              | **Build** example using precompiled "ev3dev-c" library
`release-clean`                        | **Remove** files created during building `release` target
`debug` (default)                      | **Build** example using the source files of "ev3dev-c" library
`debug-clean` or `clean`               | **Remove** all files created during building `debug` target
`debug-clean-binary` or `clean-binary` | **Remove** only binary files created during building `debug` target

### See also

[Examples in Python](../python/ev3dev/eg)<br>
[Examples in Perl](../perl/eg)<br>
[Examples in Ruby](../ruby/eg)
