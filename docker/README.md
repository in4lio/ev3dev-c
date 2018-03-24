### Getting ~started~ compiled inside a Docker container

We assume that you have already installed and ran Docker and cloned
**ev3dev-c** library, so you are ready to build a Docker image. You should
use the Dockerfile from the _"ev3dev-c/docker/"_ directory, which is
referring to the ev3dev cross-compiler image but also installs _"swig3.0"_
and _"python-dev"_ packages:

    cd /PATH/TO/ev3dev-c/docker/
    docker build --rm -t ev3cc .

Once **ev3cc** image is built, you can compile the library, examples and your
programs using Docker. First, run a new Docker container, for example:

    docker run --rm -it -h ev3 -v /PATH/TO/ev3dev-c/:/home/robot/ev3dev-c -w /home/robot/ev3dev-c ev3cc /bin/bash

Before that, in case you are using MinGW MSYS, you may need to execute:

    export MSYS_NO_PATHCONV=1

You have to take into account that, by default, the preprocessing stage
is skipping when compilation is performed on the brick or using Docker.
Please set `SKIP_PP = 0` in the makefile to allow preprocessing anywhere.

After that, inside the container, you are able to compile and install
static and shared libraries:

    cd source/ev3/
    make
    sudo make install
    make shared
    sudo make shared-install

That's all, now you can try to compile one of the examples:

    cd ../../eg/hello/
    make

See also – ["Using Docker to Cross-Compile"][ev3dev-cross]

[ev3dev-cross]: http://www.ev3dev.org/docs/tutorials/using-docker-to-cross-compile/
