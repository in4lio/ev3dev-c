## Compilation notes

### How to make and install STATIC library

    cd ev3dev-c/source/ev3/
    make
    sudo make install

### How to make and install SHARED library

    cd ev3dev-c/source/ev3/
    make shared
    sudo make shared-install

### How to use SHARED library

    cd ev3dev-c/eg/port/
    gcc port.c -lev3dev-c -o port

    ./port
