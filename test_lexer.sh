#!/bin/bash

# Make lexer
make clean
make bin/c_lexer

# make test files
mkdir -p test/lexer/in
echo -e "#include <stdio.h>\nint main(){\n  printf(\"Wibble\"); \n}\n" > test/lexer/in/tmp.c
echo -e "#include \"wib.c\"\nint main(){\n  printf(\"Wibble\"); \n}\n" > test/lexer/in/wibble.c
echo -e "int main(){\n  printf(\"Wib\"); \n}\n" > test/lexer/in/wib.c

# make test results directory
mkdir -p test/lexer/out

# iterate through in directory
for i in test/lexer/in/*.c; do
  echo "==========================="
  echo "Input file : ${i}"
  BASENAME=$(basename $i .c);
  # Preprocess the files and pass ouotput into c_lexer
  cpp $i | ./bin/c_lexer > test/lexer/out/$BASENAME.stdout.txt 2> test/lexer/out/$BASENAME.stderr.txt
done
