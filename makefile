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
	bison -d -o include/c_parser.tab.c -d $^
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
_PSRCS=
PSRCS=$(patsubst %,$(PSDIR)/%,$(_PSRCS))

bin/c_parser: $(PSRCS:%.cpp=%.o)
	mkdir -p bin
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $^
	

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
	rm -f include/*.tab.*

.PHONY: clean
