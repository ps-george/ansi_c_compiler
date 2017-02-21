CXXFLAGS += -std=c++11 -W -Wall -g
# Set constant directorys
LSDIR=src/lexer
PSDIR=src/parser
CSDIR=src/compiler

INC=-Iinclude
# Preprocessor flags, MMD creates dependency files
CPPFLAGS += -MMD $(INC)

###
### BUILD RULES FOR LEXER
###
# List of source files for lexer
_LSRCS= lexer_main.cpp flexer.yy.cpp
LSRCS=$(patsubst %,$(LSDIR)/%,$(_LSRCS))

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
_PSRCS=parser_main.cpp flexer.yy.cpp c_parser.tab.c
PSRCS=$(patsubst %,$(PSDIR)/%,$(_PSRCS)) src/ast/ast.cpp

bin/c_parser: include/c_parser.tab.h $(PSRCS:%.cpp=%.o) 
	mkdir -p bin
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $(PSRCS:%.cpp=%.o)

%/flexer.yy.cpp: src/lexer/flexer.flex include/c_parser.tab.h
	flex -o $@ $^

%/c_parser.tab.c: include/c_parser.tab.h

-include $(_PSRCS:%.cpp=%.d)

###
### BUILD RULES FOR COMPILER
###
# Source files
_CSRCS=
CSRCS=$(patsubst %,$(CSDIR)/%,$(_CSRCS))
bin/c_compiler : $(CSRCS:%.cpp=%.o)
	mkdir -p bin
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

-include $(_CSRCS:%.cpp=%.d)

clean:
	rm -f bin/*
	rm -f src/lexer/*.o
	rm -f src/lexer/*.d
	rm -f include/*.tab.*
	rm -f src/parser/*.o
	rm -f src/parser/*.d
	rm -f src/parser/*.tab.*
	rm -f src/parser/*.yy.*
	rm -f src/ast/*.o
	rm -f src/ast/*.d

.PHONY: clean
