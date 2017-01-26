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

bin/c_lexer: $(LSRCS:%.cpp=%.o)
	mkdir -p bin
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

# Need to generate flexer.yy.cpp from .flex first
%/flexer.yy.cpp: %/flexer.flex
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

.PHONY: clean
