#!/bin/bash

# Make lexer
make clean
make bin/c_parser

# make test results directory
mkdir -p test/c/out
PASSED=0
CHECKED=0

for i in test/parser/in/*.c; do
  echo "==========================="
  echo "Input file : ${i}"
  BASENAME=$(basename $i .c);
  cat $i | ./bin/c_parser c > test/c/out/$BASENAME.stdout.c
  if [[ "$?" -ne "0" ]]; then
      echo -e "\nERROR"
  else
      PASSED=$(( ${PASSED}+1 ));
  fi
  CHECKED=$(( ${CHECKED}+1 ));
  # Can use tidy to prettify output for comparison with others/if xml is formatted not perfectly
  
  # diff <(cat test/parser/out/$BASENAME.stdout.txt) <(cat test/parser/out/$BASENAME.tidy.txt) > test/parser/out/$BASENAME.diff.txt 2> /dev/null
  
done
echo ""
echo "Passed ${PASSED} out of ${CHECKED}".

if [ "${PASSED}" == "${CHECKED}" ]; then
  exit 0
else
  exit 1
fi
  
