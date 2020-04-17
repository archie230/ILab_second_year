GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

C++ = g++

G++_FLAGS = -I $(GOOGLE_TEST_INCLUDE)
C++_FLAGS = -Wall -std=c++17

LD_FLAGS = -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread

SOURCEDIR = ../src/
OBJECTS = unit_tests.o
TARGET = tests

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(C++) -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

unit_tests.o : unit_tests.cpp ../matrix.hpp
	$(C++) -c $(G++_FLAGS) $(C++_FLAGS) $<

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
