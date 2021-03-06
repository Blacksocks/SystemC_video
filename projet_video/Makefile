SYSTEMC   ?= /comelec/softs/opt/systemc/current
ARCH      ?= linux64

CC        = gcc
CXX       = g++

CFLAGS   +=  -g -Wall
CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -O2 -g -std=c++11
LDFLAGS   =  -g -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc -pthread -lpng

SOURCES_CPP = $(wildcard *.cpp)
SOURCES_C   = $(wildcard *.c)
OBJS        = $(patsubst %.cpp,%.o,$(SOURCES_CPP))
OBJS       += $(patsubst %.c,%.o,$(SOURCES_C))
EXE         = simulation.x

DEPS = $(patsubst %.o,.%.d,$(OBJS))
ARGS = 3000000 mean zoom

.PHONY: all run display clean compare

all: run

$(EXE) : $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@  $(LDLIBS) 2>&1 | c++filt

run: $(EXE)
	./$< $(ARGS)

display: simulation_trace.vcd
	gtkwave $<

compare:
	convert wallace00.png gray:imgIn.bin
	convert img_00_out.png gray:imgOut.bin
	hexdiff imgIn.bin imgOut.bin
	rm imgIn.bin imgOut.bin

clean :
	-rm -f $(EXE)
	-rm -f $(OBJS)
	-rm -f $(DEPS)
	-rm -f *.vcd
	-rm -f *~ *_old
	-rm -f core
	-rm -f *_out.png

.%.d:%.c
	$(CC) $(CPPFLAGS) -MM -MF $@ -MT $(patsubst %.c,%.o,$<) $<
.%.d:%.cpp
	$(CXX) $(CPPFLAGS) -MM -MF $@ -MT $(patsubst %.cpp,%.o,$<) $<

ifneq ($(MAKECMMGOALS),clean)
-include $(DEPS)
endif
