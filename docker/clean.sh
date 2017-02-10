#! /bin/sh

# docker stop $(docker ps -a -q)
# docker rm $(docker ps -a -q)
li=$(docker images -f "dangling=true" -q)
[ -z "$li" ] || docker rmi $(li)
