CC=g++
CFLAGS=-std=c++17 -g -Wall
LIBS=-lstdc++
SOURCES= IntersectionArea.cpp
OBJECTS= $(SOURCES:.cpp=.o)
EXECUTABLE=interarea

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^

clear:
	rm -rf $(EXECUTABLE) *.o *.s

interarea.s:
	$(CC) $(CFLAGS) $(SOURCES) -S -o $@

exe: $(EXECUTABLE)
	@echo
	@./$(EXECUTABLE)
	@echo
	@echo