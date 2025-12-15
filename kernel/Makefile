# project variables
BINARY_NAME=kernel
SHEDSKIN_LIBDIR=$(CURDIR)/clib
# $(HOME)/venv/lib/python3.13/site-packages/shedskin/lib
CPPFILES=$(GENERATED_CPPFILES) $(BUILTIN_CPPFILES)
HPPFILES=$(GENERATED_HPPFILES) $(BUILTIN_HPPFILES)

INCLUDEDIRS=-I$(CURDIR) -I$(SHEDSKIN_LIBDIR) -I/usr/include
LINKDIRS=-L/usr/lib -L/usr/local/lib

CXX=g++
CXXFLAGS+=-O2 -std=c++20 -march=native $(CPPFLAGS) -D__SS_INT64 -D__SS_FLOAT64 -D__SS_NOGC $(INCLUDEDIRS)
LDFLAGS+= $(LINKDIRS)
LDLIBS=-lgc -lgctba #-lutil

BUILTIN_CPPFILES=$(SHEDSKIN_LIBDIR)/builtin.cpp
BUILTIN_HPPFILES=$(SHEDSKIN_LIBDIR)/builtin.hpp
GENERATED_CPPFILES=\
	$(CURDIR)/gen_cxx/main.cpp \
	$(CURDIR)/gen_cxx/constants.cpp

GENERATED_HPPFILES=\
	$(CURDIR)/gen_cxx/main.hpp \
	$(CURDIR)/gen_cxx/constants.hpp


.PHONY: all clean

all: kernel

kernel: $(CPPFILES) $(HPPFILES)
	$(CXX)  $(CXXFLAGS) $(CPPFILES) $(LDLIBS) $(LDFLAGS) -o $(BINARY_NAME)

kernel_debug: $(CPPFILES) $(HPPFILES)
	$(CXX) -g -ggdb $(CXXFLAGS) $(CPPFILES) $(LDLIBS) $(LDFLAGS) -o $(BINARY_NAME)_debug

kernel_prof: $(CPPFILES) $(HPPFILES)
	$(CXX) -pg -ggdb $(CXXFLAGS) $(CPPFILES) $(LDLIBS) $(LDFLAGS) -o $(BINARY_NAME)_prof

clean:
	@rm -rf kernel kernel_prof kernel_debug

reset: clean
	@rm -f $(GENERATED_CPPFILES) $(GENERATED_HPPFILES)

