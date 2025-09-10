##
# TUMuchData Coding Challenge 2025
#

CXX ?= g++
CXXFLAGS := -std=c++23 -g -Wall 

INCLUDES := Parameters.hpp User.hpp FileUtils.hpp

build: main.cpp  $(INCLUDES)
	$(CXX) $(CXXFLAGS) main.cpp -o main.out

default_run: build
	./main.out 1 1 ../data/sample

clean:
	rm -f *.out
.PHONY: clean
