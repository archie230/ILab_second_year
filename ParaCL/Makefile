CXXFLAGS=-g -std=c++17 -pedantic-errors
CXX=g++

PARS_DIR=src/parser/
LEX_DIR=src/lexer/
SRC_DIR=src/
BIN_DIR=bin/

OBJECTS=parser.o lexer.o driver.o ast.o symtbl.o interpreter.o
BISONFLAGS=-t -v
FLEXFLAGS=-d

.PHONY: all clean debug

all: interpreter

debug: CXXFLAGS += -DDEBUG
debug: interpreter

clean:
	rm bin/*
	rm -i bin

interpreter: $(OBJECTS)
	cd bin; $(CXX) $(OBJECTS) -o $@;

parser.o: $(PARS_DIR)parser.cc $(PARS_DIR)parser.hh $(PARS_DIR)stack.hh
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

lexer.o: $(LEX_DIR)lexer.cc
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

interpreter.o: $(SRC_DIR)interpreter.cc
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

driver.o: $(SRC_DIR)PCL_Driver.cc $(SRC_DIR)PCL_Driver.hpp
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

ast.o: $(SRC_DIR)AST.cc $(SRC_DIR)AST.hpp
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

symtbl.o: $(SRC_DIR)SymTbl.cc $(SRC_DIR)SymTbl.hpp
	$(CXX) $(CXXFLAGS) $< -c -o $(BIN_DIR)$@

$(LEX_DIR)lexer.cc: $(LEX_DIR)lexer.l
	flex $(FLEXFLAGS) -o $@ $(LEX_DIR)lexer.l

$(PARS_DIR)parser.cc: $(PARS_DIR)parser.y
	bison $(BISONFLAGS) $(PARS_DIR)parser.y -o $@
