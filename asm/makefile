TOP = ..

YUPP_HOME = $(TOP)/yupp
PP = python -u $(YUPP_HOME)/yup.py

E_YU = .yu
E_YUH = .yu-h
E_H = .h

D_EV3 = $(TOP)/source/ev3

PPFLAGS = -q --pp-browse $(addprefix -d, $(D_EV3))

S_YU = $(wildcard $(addsuffix /*$(E_YU), ./)) $(wildcard $(addsuffix /*$(E_YU), $(TOP)/source/ev3))
S_YUH = $(wildcard $(addsuffix /*$(E_YUH), ./))

G_H = $(addsuffix $(E_H), $(basename $(S_YUH)))

.PHONY: default all clean

default: $(G_H)
all: default

$(G_H): $(S_YU)

$(G_H): %$(E_H): %$(E_YUH)
	$(PP) $(PPFLAGS) $<

clean:
	-rm -f *.h
