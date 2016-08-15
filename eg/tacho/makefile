TARGET = tacho

LIBS = -lm -lev3dev-c

ifeq ($(OS),Windows_NT)
LIBS := $(LIBS) -lws2_32
endif

CC = gcc
CFLAGS = -O2 -std=gnu99 -W -Wall -Wno-comment

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
