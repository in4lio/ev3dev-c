# We have to use "armel-cross" if we want to build Python module.
FROM ev3dev/debian-jessie-armel-cross:latest
# FROM ev3dev/debian-jessie-cross:latest

RUN sudo apt-get update
RUN sudo apt-get install -y swig3.0 python-dev
RUN sudo rm -rf /var/lib/apt/lists/*
