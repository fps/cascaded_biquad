CXXFLAGS ?= -I include/ -std=c++17 -O2
all: test

test: test.cc include/cascaded_biquad.h noise.h

