#SYSTEMC   ?= /comelec/softs/opt/systemc/current
SYSTEMC   ?= /usr/local
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc
EXE       = hello

all: run clean

run: $(EXE)
	./$<

clean:
	rm -f $(EXE)
