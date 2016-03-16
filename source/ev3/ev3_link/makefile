TARGET = ev3_link

LIBS = -lm

ifeq ($(OS),Windows_NT)
LIBS := $(LIBS) -lws2_32
endif

CC = gcc

D_C = . ../../../3d_party
D_H = $(D_C)

CFLAGS = $(addprefix -I, $(D_H)) -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard $(addsuffix /*.c, $(D_C))))
HEADERS = $(wildcard $(addsuffix /*.h, $(D_H)))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
