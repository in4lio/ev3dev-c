### Getting ~started~ compiled inside a Docker container

We assume that you have already installed and ran Docker and cloned
**ev3dev-c** library, so you are ready to build a Docker image:

    cd /PATH/TO/ev3dev-c/docker/
    docker build --rm -t ev3cc -f <dockerfile> .

where <dockerfile> is the path to one of the Docker configuration files in the Dockerfiles subfolder, e.g.:
     Dockerfiles/debian-jessie-armel-cross-pydev.dockerfile

Once **ev3cc** image is built, you can compile the library, examples and your
programs using Docker. First, run a new Docker container, for example:

    docker run --rm -it -h ev3 -v /PATH/TO/ev3dev-c/:/home/robot/ev3dev-c -w /home/robot/ev3dev-c ev3cc /bin/bash

Before that, in case you are using MinGW MSYS, you may need to execute:

    export MSYS_NO_PATHCONV=1

After that, inside the container, you have to compile and install static and
shared libraries:

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
