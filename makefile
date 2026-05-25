CXXFLAGS ?= -I. -std=c++17
all: test

test: test.cc cascaded_biquad.h noise.h

