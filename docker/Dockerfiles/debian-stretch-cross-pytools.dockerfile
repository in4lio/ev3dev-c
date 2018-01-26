FROM ev3dev/debian-stretch-cross

# Install python tools needed for cross builds
RUN sudo apt-get update && \
    DEBIAN_FRONTEND=noninteractive sudo apt-get install --yes --no-install-recommends \
        python \
        scons && \
    sudo rm -rf /var/lib/apt/lists/*
