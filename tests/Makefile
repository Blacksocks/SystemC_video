#SYSTEMC   ?= /comelec/softs/opt/systemc/current
SYSTEMC   ?= /usr/local
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc
EXE       =  pixel_thread

all: run clean

run: $(EXE)
	./$< $(ARGS)

display: my_simu_trace.vcd
	gtkwave $<

clean:
	rm -f $(EXE)
