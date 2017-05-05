SYSTEMC   ?= /comelec/softs/opt/systemc/current
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc
EXE       = test_integers

all: run clean

run: $(EXE)
	./$<

clean:
	rm -f $(EXE)
