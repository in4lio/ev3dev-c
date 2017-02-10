#! /bin/sh

export MSYS_NO_PATHCONV=1

docker run --rm -it -h ev3dev -v "${PWD}":/home/robot/${PWD##*/} -w /home/robot/${PWD##*/} ev3cc /bin/bash
