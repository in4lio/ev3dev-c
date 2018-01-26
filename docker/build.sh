#! /bin/sh
if [ "$1" = "" ]; then
echo "Usage: $0 <dockerfile>"
else
docker build --rm -t ev3cc -f $1 .
fi
