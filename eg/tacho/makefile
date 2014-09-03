#                  _ _     _
#    ___ ___ ___ _| |_|___| |_
#   |   |  _   _|   | |  _   _|
#   |  _|_| |___ ___|_|___  |
#   |_|                   |_|
#   yu-c makefile

# -- binary name (without extension)
BIN = tacho

# -- creating MAP file
MAP = 0

ifeq ($(OS),Windows_NT)
# -- platform (core)
# ARM Cortex-M3: __MDKARM__
# DOS: __DJGPP__
# WIN32: __MINGW__
# UNIX: __UNIX__
PLATFORM = __MINGW__
EV3 = 0
else
PLATFORM = __UNIX__
# -- EV3 BOARD
EV3 = $(if $(shell $(CC) -dM -E - < /dev/null | grep __ARM_ARCH_4T__),1,0)
endif

YUPP_HOME = ../../yupp

# -- preprocessor (yupp)
PP = python -u $(YUPP_HOME)/yup.py

# -- compilers
ifeq ($(PLATFORM),__DJGPP__)
CC = $(DJGPP_HOME)/bin/gcc.exe
CXX = $(DJGPP_HOME)/bin/gxx.exe
else
CC = gcc
CXX = g++
endif

# -- output subdirectory
ifeq ($(PLATFORM),__DJGPP__)
D_PLATFORM = djgpp
else

ifeq ($(PLATFORM),__MINGW__)
D_PLATFORM = mingw
else
D_PLATFORM =
endif

endif

# -- platform specific options
ifeq ($(PLATFORM),__DJGPP__)
BUFSIZE = 16k
MINSTACK = 1024k
endif

# -- yupp import directories
D_YU = ../../source/ev3

# -- source directories
D_C = . ../../source/ev3 ../../lib
ifeq ($(EV3),0)
D_C := $(D_C) ../../source/ev3/ev3_link
endif

D_CXX = $(D_C)
D_ASM = source

D_C := $(if $(D_PLATFORM), source/$(D_PLATFORM) $(D_C), $(D_C))

# -- include directories
D_H = $(D_C)

# -- binary directory
D_BIN = bin
D_BIN := $(if $(D_PLATFORM), $(D_BIN)/$(D_PLATFORM), $(D_BIN))

# -- object directory
D_OBJ = object
D_OBJ := $(if $(D_PLATFORM), $(D_OBJ)/$(D_PLATFORM), $(D_OBJ))

# -- LIST and MAP directories
D_MAP = object
D_LIST = object

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
E_BIN = .exe
else
E_BIN =
endif

# -- LIST and MAP suffixes
E_MAP = .map
E_LIST = .listing

# -- link options
LIBS = -lm
ifeq ($(PLATFORM),__MINGW__)
LIBS := $(LIBS) -lws2_32
endif

LFLAGS =

ifeq ($(MAP),1)
LFLAGS := $(LFLAGS) -Wl,-Map,$(D_MAP)/$(BIN)$(E_MAP)
endif

# -- preprocessor flags
PPFLAGS = --pp-no-skip-c-comment -q $(addprefix -d, $(D_YU))

# -- compiler flags
CFLAGS = $(addprefix -I, $(D_H)) -O2 -W -Wall -Wno-comment -std=gnu99
CXXFLAGS = $(addprefix -I, $(D_H)) -O2 -ffast-math -funroll-loops -fno-exceptions -fomit-frame-pointer -g -W -Wall -Wno-comment
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

define uniq =
	$(eval seen :=)
	$(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
	${seen}
endef

S_C = $(sort $(wildcard $(addsuffix /*$(E_C), $(D_C))) $(G_C))
$(call uniq, $(S_C)) # remove duplicates

S_CXX = $(sort $(wildcard $(addsuffix /*$(E_CXX), $(D_CXX))) $(G_CXX))
$(call uniq, $(S_CXX)) # remove duplicates

S_ASM = $(wildcard $(addsuffix /*$(E_ASM), $(D_ASM)))

O_CXX = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_CXX)))))
O_C = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_C)))))
O_ASM = $(addprefix $(D_OBJ)/, $(addsuffix $(E_OBJ), $(basename $(notdir $(S_ASM)))))

O = $(O_CXX) $(O_C) $(O_ASM)

# ---------------------------------
#   commands
# ---------------------------------

# -- compiler wrapper
ifeq ($(OS),Windows_NT)
# -- too long command line workaround
define wrap
	echo $2 > .\args
	$1 @.\args
	del .\args
endef
else
define wrap
	$1 $2
endef
endif

# -- optional final tools
ifeq ($(PLATFORM),__DJGPP__)
define final
	stubedit $1 minstack=$(MINSTACK) bufsize=$(BUFSIZE)
endef
else
define final
endef
endif

# -- removal list
R = $(D_BIN)/$(BIN)$(E_BIN) $(O) $(G_H) $(G_C) $(G_CXX)
ifeq ($(MAP),1)
R := $(R) $(D_MAP)/$(BIN)$(E_MAP)
endif

ifeq ($(OS),Windows_NT)
#CLEAN = cmd /c "del $(subst /,\,$(R))"
CLEAN = rm -rf $(R)
else
CLEAN = rm -rf $(R)
endif

# -- install
ifeq ($(OS),Windows_NT)
INSTALL =
else
INSTALL =
endif

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

all: $(D_BIN)/$(BIN)$(E_BIN)

$(D_BIN)/$(BIN)$(E_BIN) : $(O)
	$(call wrap,$(CC),$^ -o $@ $(LIBS) $(LFLAGS))
	$(call final,$@)
	@echo "*** $(D_BIN)/$(BIN)$(E_BIN) ***"

$(G_C) $(G_CXX) $(G_H) : $(S_YU)

$(G_C) : %$(E_C) : %$(E_YUC)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(G_CXX) : %$(E_CXX) : %$(E_YUCXX)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(G_H) : %$(E_H) : %$(E_YUH)
	$(call wrap,$(PP),$(PPFLAGS) $<)

$(S_C) $(S_CXX) : $(G_H)

$(O_C) : $(D_OBJ)/%$(E_OBJ) : %$(E_C)
	$(call wrap,$(CC),$(CFLAGS) -c $< -o $@)

$(O_CXX) : $(D_OBJ)/%$(E_OBJ) : %$(E_CXX)
	$(call wrap,$(CXX),$(CXXFLAGS) -c $< -o $@)

$(O_ASM) : $(D_OBJ)/%$(E_OBJ) : %$(E_ASM)
	$(call wrap,$(CC),$(ASMFLAGS) -c $< -o $@)

# -- remove temporary files
.PHONY: clean

clean:
	$(CLEAN)

# -- install project
.PHONY: install

install:
	$(INSTALL)

# -- EOF
