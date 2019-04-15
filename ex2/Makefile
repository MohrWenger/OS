CXX=g++
RANLIB=ranlib

LIBSRC=uthreads.cpp
LIBOBJ=$(LIBSRC:.cpp=.o)

INCS=-I.
CXXFLAGS = -Wall -std=c++11 -g $(INCS)

UTHRLIB = libuthreads.a
TARGETS = $(UTHRLIB)

TAR=tar
TARFLAGS=-cvf
TARNAME=ex2.tar
TARSRCS=$(LIBSRC) Makefile README

all: $(TARGETS)

$(TARGETS): $(LIBOBJ)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

clean:
	$(RM) $(TARGETS) $(UTHRLIB) $(OBJ) $(LIBOBJ) *~ *core

depend:
	makedepend -- $(CXXFLAGS) -- $(SRC) $(LIBSRC)

tar:
	$(TAR) $(TARFLAGS) $(TARNAME) $(TARSRCS)

