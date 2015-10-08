#                  _ _     _
#    ___ ___ ___ _| |_|___| |_
#   |   |  _   _|   | |  _   _|
#   |  _|_| |___ ___|_|___  |
#   |_|                   |_|
#   makefile ( yupp, SWIG, gcc )

# -- binary name (without prefix and extension)
BIN = ev3

# -- platform (core)
ifeq ($(OS),Windows_NT)
# WIN32
PLATFORM = __MINGW__
else
# UNIX
PLATFORM = __UNIX__
endif

TOP = ..

# -- compilers
CC = gcc
CXX = g++
LINK = $(CC)

# -- on EV3 BRICK
ifeq ($(PLATFORM),__UNIX__)
EV3 = $(if $(shell $(CC) -dM -E - < /dev/null | grep __ARM_ARCH_4T__),1,0)
else
EV3 = 0
endif

# -- yupp preprocessor
YUPP_HOME = $(TOP)/yupp

# -- perform preprocessing anywhere
# SKIP_PP = 0
# -- skip preprocessing on the EV3 brick (it's a bit slow), would be better to use pre-generated sources
SKIP_PP = $(EV3)
# -- skip preprocessing anywhere
# SKIP_PP = 1

ifeq ($(SKIP_PP),0)
PP = python -u $(YUPP_HOME)/yup.py
else
PP = @echo makefile: warning: preprocessing step is skipped,
endif

# -- simplified wrapper and interface generator
SWIG = swig

# -- output subdirectory
ifeq ($(PLATFORM),__MINGW__)
D_PLATFORM = mingw
else
D_PLATFORM =
endif

# -- ruby directory
D_RUBY = d:/prog/ruby

# -- yupp import directories
D_YU = $(TOP)/source/ev3

# -- source directories
D_C = $(D_YU) $(TOP)/3d_party

ifeq ($(EV3),0)
D_C := $(D_C) $(TOP)/source/ev3/ev3_link
endif

D_CXX = $(D_C)
D_ASM = $(TOP)/source

# -- ruby headers
ifndef RUBY_INCLUDE

ifeq ($(PLATFORM),__MINGW__)
RUBY_INCLUDE = $(D_RUBY)/include/ruby-2.0.0
else

ifeq ($(PLATFORM),__UNIX__)
RUBY_INCLUDE = /usr/include/ruby-2.1.0 /usr/include/arm-linux-gnueabi/ruby-2.1.0
endif

endif

endif

# -- include directories
D_H = $(D_C) $(RUBY_INCLUDE)

# -- binary directory
D_BIN = .
D_BIN := $(if $(D_PLATFORM), $(D_BIN)/$(D_PLATFORM), $(D_BIN))

# -- object directory
D_OBJ = $(TOP)/object
D_OBJ := $(if $(D_PLATFORM),$(D_OBJ)/$(D_PLATFORM),$(D_OBJ))

# -- swig interface file source
F_SWIG_YUI = $(TOP)/ev3.yu-i

# -- basename of swig wrap file
F_WRAP_BASE = $(if $(D_PLATFORM),$(D_PLATFORM)/$(BIN),$(BIN))_wrap

# -- source code suffix
E_YU = .yu
E_YUH = .yu-h
E_YUC = .yu-c
E_YUCXX = .yu-cpp

E_H = .h
E_C = .c
E_CXX = .cpp
E_ASM = .asm

# -- object suffix
E_OBJ = .o

# -- binary suffix
ifeq ($(OS),Windows_NT)
E_BIN = .so
else
E_BIN = .so
endif

# -- the rest of removal list
G_REST = $(F_WRAP_BASE).c platform.h

ifeq ($(SKIP_PP),0)
G_REST := $(BIN).i
endif

# -- binary full name
F_BIN = $(D_BIN)/$(BIN)$(E_BIN)

# -- link options
LIBS = -lm

ifeq ($(PLATFORM),__MINGW__)

ifndef RUBY_LIB
RUBY_LIB = $(D_RUBY)/lib
endif

LIBS := $(LIBS) -lws2_32 -lmsvcrt-ruby200.dll -L$(RUBY_LIB)
else

ifeq ($(PLATFORM),__UNIX__)
LIBS := $(LIBS) -lruby-2.1
endif

endif

LFLAGS =

# -- preprocessor flags
PPFLAGS = -q --pp-browse $(addprefix -d, $(D_YU))

# -- compiler flags
CFLAGS = $(addprefix -I, $(D_H)) -O2 -std=gnu99 -W -Wall -Wno-comment -Wno-unused-parameter

ifeq ($(PLATFORM),__UNIX__)
CFLAGS := $(CFLAGS) -fPIC
endif

CXXFLAGS = $(addprefix -I, $(D_H)) -O2 -ffast-math -funroll-loops -fno-exceptions -fomit-frame-pointer -g -W -Wall -Wno-comment

ifeq ($(PLATFORM),__UNIX__)
CXXFLAGS := $(CXXFLAGS) -fPIC
endif

ASMFLAGS = -Wall

# ---------------------------------
#   files lists
# ---------------------------------

S_YU = $(wildcard $(addsuffix /*$(E_YU), $(D_YU)))
S_YUH = $(wildcard $(addsuffix /*$(E_YUH), $(D_H)))
S_YUC = $(wildcard $(addsuffix /*$(E_YUC), $(D_C)))
S_YUCXX = $(wildcard $(addsuffix /*$(E_YUCXX), $(D_CXX)))

G_CXX = $(addsuffix $(E_CXX), $(basename $(S_YUCXX)))
G_C = $(addsuffix $(E_C), $(basename $(S_YUC)))
G_H = $(addsuffix $(E_H), $(basename $(S_YUH)))

S_C = $(sort $(wildcard $(addsuffix /*$(E_C), $(D_C))) $(G_C))
S_CXX = $(sort $(wildcard $(addsuffix /*$(E_CXX), $(D_CXX))) $(G_CXX))
S_ASM = $(wildcard $(addsuffix /*$(E_ASM), $(D_ASM)))

O_CXX = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_CXX)))))
O_C = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_C)))))
O_ASM = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_ASM)))))

O = $(O_CXX) $(O_C) $(O_ASM)

# ---------------------------------
#   commands
# ---------------------------------

# -- wrap compiler arguments
ifeq ($(OS),Windows_NT)
# -- too long command line workaround
define wrap
	echo $2 > args
	$1 @args
	-rm args
endef
else
define wrap
	$1 $2
endef
endif

# -- optional final tools
define final
endef

# -- removal list
R_BIN = $(F_BIN) $(O) $(G_REST)
R = $(R_BIN)

ifeq ($(SKIP_PP),0)
R := $(R) $(G_H) $(G_C) $(G_CXX)
endif

ifeq ($(OS),Windows_NT)
#CLEAN = cmd /c "del $(subst /,\,$(R))"
CLEAN = rm -rf $(R)
else
CLEAN = rm -rf $(R)
endif

CLEAN_BIN = rm -rf $(R_BIN)

# -- install
define install

endef

# ---------------------------------
#   make rules
# ---------------------------------

vpath %$(E_CXX) $(D_CXX)
vpath %$(E_C) $(D_C)
vpath %$(E_ASM) $(D_ASM)
vpath %$(E_YUCXX) $(D_CXX)
vpath %$(E_YUC) $(D_C)

# -- build project
.PHONY: all

all: $(F_BIN)

$(F_BIN): $(O) $(F_WRAP_BASE).o
	$(call wrap,$(LINK),-shared $^ -o $@ $(LIBS) $(LFLAGS))
	$(call final,$@)
	@echo "*** $(F_BIN) ***"

$(F_WRAP_BASE).c: $(BIN).i
	echo \#define EV3_BRICK $(EV3) > ./platform.h
	$(SWIG) -ruby -o $(F_WRAP_BASE).c $<

$(BIN).i: $(F_SWIG_YUI) $(S_YUH)
	$(call wrap,$(PP),$(PPFLAGS) -o. $<)

$(G_C) $(G_CXX) $(G_H): $(S_YU)

$(G_C): %$(E_C): %$(E_YUC)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(G_CXX): %$(E_CXX): %$(E_YUCXX)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(G_H): %$(E_H): %$(E_YUH)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(S_C) $(S_CXX): $(G_H)

$(O_C): $(D_OBJ)/%$(E_OBJ): %$(E_C)
	$(call wrap,$(CC),$(CFLAGS) -c $< -o $@)

$(O_CXX): $(D_OBJ)/%$(E_OBJ): %$(E_CXX)
	$(call wrap,$(CXX),$(CXXFLAGS) -c $< -o $@)

$(O_ASM): $(D_OBJ)/%$(E_OBJ): %$(E_ASM)
	$(call wrap,$(CC),$(ASMFLAGS) -c $< -o $@)

# -- remove temporary files
.PHONY: clean

clean:
	$(CLEAN)

# -- remove binary files
.PHONY: clean-binary

clean-binary:
	$(CLEAN_BIN)

# -- install project
.PHONY: install

install:
	$(call install)

# -- EOF
