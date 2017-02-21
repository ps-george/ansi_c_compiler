#!/bin/bash

# Make lexer
make clean
make bin/c_parser

# make test results directory
mkdir -p test/ast/out
PASSED=0
CHECKED=0

for i in test/ast/in/*.c; do
  echo "==========================="
  echo "Input file : ${i}"
  BASENAME=$(basename $i .c);
  # Compile original program
  # gcc -o test/ast/ref/$BASENAME $i
  # Run original program and save output as reference
  
  
  cat $i | ./bin/c_parser c > test/ast/out/$BASENAME.c
  
  # Compile ast created program
  # gcc -o test/ast/out/$BASENAME test/ast/out/$BASENAME.c
  # Run ast created program and diff with the output from original program
  
  if [[ "$?" -ne "0" ]]; then
      echo -e "\nERROR"
  else
      PASSED=$(( ${PASSED}+1 ));
  fi
  CHECKED=$(( ${CHECKED}+1 ));
  
done
echo ""
echo "Passed ${PASSED} out of ${CHECKED}".

if [ "${PASSED}" == "${CHECKED}" ]; then
  exit 0
else
  exit 1
fi
  
