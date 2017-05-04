TARGET = $(notdir $(shell pwd))

LIBS = -lm -lev3dev-c
D_BIN = Release

ifeq ($(OS),Windows_NT)
LIBS := $(LIBS) -lws2_32 -Wl,-rpath=../../lib/mingw -L../../lib/mingw
D_BIN := $(D_BIN)/mingw
endif

D_H = ../../source/ev3
CFLAGS = $(addprefix -I, $(D_H)) -O2 -std=gnu99 -W -Wall -Wno-comment
CXXFLAGS = $(addprefix -I, $(D_H)) -O2 -g -W -Wall -Wno-comment

ifeq ($(OS),Windows_NT)
CC = gcc
CXX = g++
else
CC = arm-linux-gnueabi-gcc
CXX = arm-linux-gnueabi-g++
endif

ifeq ($(OS),Windows_NT)
E_BIN = .exe
else
E_BIN =
endif
F_BIN = $(D_BIN)/$(TARGET)$(E_BIN)

C_OBJS = $(addprefix $(D_BIN)/, $(patsubst %.c, %.o, $(wildcard *.c)))
CXX_OBJS = $(addprefix $(D_BIN)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

.PHONY: default all clean

default: $(F_BIN)
all: default

$(C_OBJS): $(D_BIN)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CXX_OBJS): $(D_BIN)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PRECIOUS: $(F_BIN) $(C_OBJS) $(CXX_OBJS)

$(F_BIN): $(C_OBJS) $(CXX_OBJS)
	$(CXX) $(C_OBJS) $(CXX_OBJS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(D_BIN)/*.o
	-rm -f $(F_BIN)
