# We have to use "armel-cross" if we want to build Python module.
FROM ev3dev/debian-jessie-armel-cross:latest
# FROM ev3dev/debian-jessie-cross:latest

# Optimize docker image layers
RUN sudo apt-get update && \
    DEBIAN_FRONTEND=noninteractive sudo apt-get install --yes --no-install-recommends \
        swig3.0 \
        python-dev && \
    sudo rm -rf /var/lib/apt/lists/*
