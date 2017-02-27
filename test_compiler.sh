#!/bin/bash

# Make lexer
make clean
make bin/c_compiler

# make test results directory
mkdir -p test/compiler/out
PASSED=0
CHECKED=0

for i in test/compiler/in/*.c; do
  echo "==========================="
  echo "Input file : ${i}"
  BASENAME=$(basename $i .c);
  
  cat $i | ./bin/c_compiler > test/compiler/out/$BASENAME.mips
  
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
  
