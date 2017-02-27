CXXFLAGS += -std=c++11 -W -Wall -g
# Set constant directorys
LSDIR=src/lexer
PSDIR=src/parser
CSDIR=src/compiler

INC=-Iinclude
# Preprocessor flags, MMD creates dependency files
CPPFLAGS += -MMD $(INC)

FLX = $(LSDIR)/flexer.yy.cpp
BIS = $(PSDIR)/c_parser.tab.c

###
### BUILD RULES FOR LEXER
###
# List of source files for lexer
LSRCS= $(LSDIR)/lexer_main.cpp $(FLX)

bin/c_lexer: include/c_parser.tab.h $(LSRCS:%.cpp=%.o) 
	mkdir -p bin
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $(LSRCS:%.cpp=%.o)

include/c_parser.tab.h: src/parser/c_parser.y
	bison -d -o include/c_parser.tab.c $^
	mv include/c_parser.tab.c src/parser/

# Need to generate flexer.yy.cpp from .flex first
%/flexer.yy.cpp: %/flexer.flex include/c_parser.tab.h
	flex -o $@ $^ 

# Need to build flexer.yy.o next
%/flexer.yy.o: flexer.yy.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

-include $(_LSRCS:%.cpp=%.d)

###
### BUILD RULES FOR PARSER
###
# Source files
PSRCS=$(PSDIR)/parser_main.cpp
-include $(PSRCS:%.cpp=%.d)
PSRCS += $(FLX) $(BIS)
PSRCS += $(wildcard src/ast/*.cpp)

bin/c_parser: include/c_parser.tab.h $(PSRCS:%.cpp=%.o) 
	mkdir -p bin
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $(PSRCS:%.cpp=%.o)

%/c_parser.tab.c: include/c_parser.tab.h

# Need to generate flexer.yy.cpp from .flex first
%/flexer.yy.cpp: %/flexer.flex include/c_parser.tab.h
	flex -o $@ $^ 

###
### BUILD RULES FOR COMPILER
###
# Source files
CSRCS=$(CSDIR)/compiler_main.cpp
-include $(CSRCS:%.cpp=%.d)
CSRCS += $(FLX) $(BIS)
CSRCS += $(wildcard src/ast/*.cpp)

bin/c_compiler : include/c_parser.tab.h $(CSRCS:%.cpp=%.o)
	mkdir -p bin
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

all : bin/c_lexer bin/c_parser bin/c_compiler

clean:
	rm -f bin/*
	rm -f src/lexer/*.o
	rm -f src/lexer/*.d
	rm -f include/*.tab.*
	rm -f src/parser/*.o
	rm -f src/parser/*.d
	rm -f src/parser/*.tab.*
	rm -f src/parser/*.yy.*
	rm -f src/compiler/*.o
	rm -f src/compiler/*.d
	rm -f src/compiler/*.tab.*
	rm -f src/compiler/*.yy.*
	rm -f src/ast/*.o
	rm -f src/ast/*.d

.PHONY: clean
