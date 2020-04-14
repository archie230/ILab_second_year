CXX=g++
CXX_FLAGS=-g -O2 -std=c++17

all: mtrx mkbin c_mtrx

mkbin:
	mkdir -p bin

mtrx:
	$(CXX) $(CXX_FLAGS) mmult-transpose.cc -o bin/mtrx

c_mtrx:
	$(CXX) $(CXX_FLAGS) mmult-transpose.c -o bin/c_mtrx
clear:
	rm bin/*