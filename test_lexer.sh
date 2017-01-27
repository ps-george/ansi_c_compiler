#!/bin/bash

# Make lexer
make bin/c_lexer

cpp src/wibble.c | ./bin/c_lexer
