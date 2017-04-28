## Examples in C

- [dc](http://in4lio.github.io/ev3dev-c/dc_8c-example.html) – Using DC motor
- [drive](http://in4lio.github.io/ev3dev-c/drive_8c-example.html) – Сomprehensive example based on coroutines
- [io](http://in4lio.github.io/ev3dev-c/io_8c-example.html) – Using low-level functions
- [light](http://in4lio.github.io/ev3dev-c/light_8c-example.html) – LEDs blinking example
- [port](http://in4lio.github.io/ev3dev-c/port_8c-example.html) – Using EV3 ports
- [poweroff](http://in4lio.github.io/ev3dev-c/poweroff_8c-example.html) – Turn the brick off remotely
- [rcx_led](http://in4lio.github.io/ev3dev-c/rcx_led_8c-example.html) – Using RCX LED
- [remote](http://in4lio.github.io/ev3dev-c/remote_8c-example.html) – IR remote control using "brick" simplified library
- [sensor](http://in4lio.github.io/ev3dev-c/sensor_8c-example.html) – TOUCH and COLOR sensors example
- [servo](http://in4lio.github.io/ev3dev-c/servo_8c-example.html) – SERVO motor example
- [tacho](http://in4lio.github.io/ev3dev-c/tacho_8c-example.html) – TACHO motor running for 5 sec
- [tacho_cpp](http://in4lio.github.io/ev3dev-c/tacho_8cpp-example.html) – TACHO motor example in C++

## See also

[Examples in Python](../python/ev3dev/eg)<br>
[Examples in Perl](../perl/eg)<br>
[Examples in Ruby](../ruby/eg)

## How to make examples?

```
> cd remote/
> make
```

Makefile targets                       | Description
:---                                   | :---
`release`                              | Build example using precompiled "ev3dev-c" library
`release-clean`                        | Remove files created during building `release` target
`debug` (default)                      | Build example using the source files of "ev3dev-c" library
`debug-clean` or `clean`               | Remove all files created during building `debug` target
`debug-clean-binary` or `clean-binary` | Remove only binary files created during building `debug` target
