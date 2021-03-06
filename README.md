[![logo](doc/pic/logo.png)](README.md)

### VERSION

    ev3dev-c    2.0a1.dev1
                2019-01-27

    kernel      4.14.80-ev3dev-2.3.1-ev3

### WHAT IS IT?

**ev3dev-c** is a C library for [LEGO MINDSTORMS EV3 Debian Linux][ev3dev]
which wraps access to the EV3 hardware.

The library also supports remote access to the EV3 brick over a network.
So, if you [configure WLAN][ev3dev-net] on the brick, you can control
the EV3 hardware from a remote computer, for example, running under Windows.

### GETTING STARTED

Before you start, make sure that you have opened an [SSH connection][ev3dev-ssh]
to your EV3 brick.

You need to install the compiler and other tools:

    sudo apt-get update
    sudo apt-get install build-essential
    sudo apt-get install git

Then, clone the library repository and its submodules to the directory
of your choice, such as _"/home/robot/ev3dev-c"_:

    cd /home/robot/
    git clone https://github.com/in4lio/ev3dev-c.git
    cd ev3dev-c/
    git submodule update --init --recursive

Compile and install static and shared libraries:

    cd source/ev3/
    make
    sudo make install
    make shared
    sudo make shared-install

It's the right time to take a look at a small example. [_"hello.c"_][hello.c]
outputs a greeting as well as toggles the left LED color:

    cd ../../eg/hello/
    more ./hello.c

Let's compile and run this program. Note that we link our example with
a static library:

    gcc hello.c -lev3dev-c -o hello
    ./hello

See also – ["Getting Started with C"][ev3dev-pure_c]

### PYTHON, RUBY and PERL

[Python](python), [Ruby](ruby) and [Perl](perl) libraries are
automatically generated from the C library using SWIG tool.

Use **pip** to install **ev3dev-c** Python package:

    pip install ev3dev-c

**ev3dev-c** Python package contains the following binary modules:
* _"\_ev3.pyd"_ – for remote control from Windows (x86)
* _"\_ev3.so"_ – for LEGO MINDSTORMS EV3 Debian

You have to install _"python-dev"_, _"ruby-dev"_ and _"libperl-dev"_
packages to build the corresponding libraries.

### GET HELP

[Documentation generated by Doxygen](http://in4lio.github.io/ev3dev-c/)

### FAQ

#### What are unusual _".yu"_, _".yu-с"_ and _".yu-h"_ files for?

**ev3dev-c** is written using [yupp lexical preprocessor][yupp] –
but don't panic – the generated source files in C also included.

You have to take into account that, by default, the preprocessing stage
is skipping when compilation is performed on the brick or using Docker.
Please set `SKIP_PP = 0` in the makefile to allow preprocessing anywhere.

#### How can I see some examples

Name           | Description
:---:          | :---
[drive.c]      | Comprehensive example based on coroutines
[remote.c]     | IR remote control using "brick" simplified library
[remote.py]    | Use of "brick" library in Python
[port.c]       | Use of EV3 ports
[sensor.c]     | TOUCH and COLOR sensors example
[tacho.c]      | TACHO motor running for 5 sec
[dc.c]         | Use of a DC motor
[servo.c]      | SERVO motor example
[light.c]      | LEDs blinking example
[rcx_led.c]    | Use of a RCX LED

[drive.c]:       http://in4lio.github.io/ev3dev-c/drive_8c-example.html
[remote.c]:      http://in4lio.github.io/ev3dev-c/remote_8c-example.html
[remote.py]:     http://in4lio.github.io/ev3dev-c/remote_8py-example.html
[port.c]:        http://in4lio.github.io/ev3dev-c/port_8c-example.html
[sensor.c]:      http://in4lio.github.io/ev3dev-c/sensor_8c-example.html
[tacho.c]:       http://in4lio.github.io/ev3dev-c/tacho_8c-example.html
[dc.c]:          http://in4lio.github.io/ev3dev-c/dc_8c-example.html
[servo.c]:       http://in4lio.github.io/ev3dev-c/servo_8c-example.html
[light.c]:       http://in4lio.github.io/ev3dev-c/light_8c-example.html
[rcx_led.c]:     http://in4lio.github.io/ev3dev-c/rcx_led_8c-example.html
[hello.c]:       http://in4lio.github.io/ev3dev-c/hello_8c-example.html

[Further examples in C...](eg)

Similar examples also available in [Python](python/ev3dev/eg),
[Ruby](ruby/eg) and [Perl](perl/eg).

#### How to make an example

For instance, to compile [_"light.c"_](eg/light) example:

    cd ev3dev-c/eg/light/
    make

    ./Debug/light

or, if you are running Windows:

    .\Debug\mingw\light.exe

#### How to control the EV3 hardware remotely

[Read here...](source/ev3/ev3_link)

#### How to use Docker for Cross-Compilation

[Read here...](docker)

#### How to make and install STATIC library

    cd ev3dev-c/source/ev3/
    make
    sudo make install

#### How to make and install SHARED library

    cd ev3dev-c/source/ev3/
    make shared
    sudo make shared-install

#### How to use SHARED library

    cd ev3dev-c/eg/port/
    gcc port.c -lev3dev-c -o port

    ./port

### GIT

Run the following on your command-line to clone the library
repository and its submodules:

    git clone https://github.com/in4lio/ev3dev-c.git
    cd ev3dev-c/
    git submodule update --init --recursive

Pull the latest library and its submodules:

    cd ev3dev-c/
    git pull origin master
    git submodule foreach git pull origin master

### CONTACT

Please feel free to contact me at in4lio+ev3@gmail.com if you have
any questions about this library.

### LICENSE

Please see the file called [_"LICENSE"_](LICENSE).

[ev3dev]: http://www.ev3dev.org/
[ev3dev-net]: http://www.ev3dev.org/docs/networking/
[ev3dev-ssh]: http://www.ev3dev.org/docs/tutorials/connecting-to-ev3dev-with-ssh/
[ev3dev-pure_c]: http://www.ev3dev.org/docs/tutorials/getting-started-with-c/
[yupp]: https://github.com/in4lio/yupp/
