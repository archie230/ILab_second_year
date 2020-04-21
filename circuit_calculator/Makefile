CXXFLAGS=-g -std=c++17 -pedantic-errors
CXX=g++

SRC_DIR=src/
PARSE_DIR=src/parser/
BIN_DIR=bin/

TARGET=circalc
OBJECTS=main.o parser.o lexer.o

BISONFLAGS=-t -v
FLEXFLAGS=-d

.PHONY: all clean debug

all: $(PARSE_DIR)parser.cc $(PARSE_DIR)lexer.cc $(TARGET)

debug: CXXFLAGS += -DDEBUG
debug: $(TARGET)

clean:
	rm -r bin

mkbin:
	mkdir -p bin

$(TARGET): mkbin $(OBJECTS)
	cd bin; $(CXX) $(OBJECTS) -o $@;

parser.o: $(PARSE_DIR)parser.cc
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

lexer.o: $(PARSE_DIR)lexer.cc
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

main.o: $(SRC_DIR)main.cc
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

$(PARSE_DIR)lexer.cc: $(PARSE_DIR)lexer.l
	flex $(FLEXFLAGS) -o $@ $(PARSE_DIR)lexer.l

$(PARSE_DIR)parser.cc: $(PARSE_DIR)parser.y
	bison $(BISONFLAGS) $(PARSE_DIR)parser.y -o $@