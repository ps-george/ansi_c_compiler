#!/bin/bash

# Make compiler
make clean
make -B bin/c_compiler

# make test results directory
mkdir -p test/compiler/out
mkdir -p test/compiler/ref
PASSED=0
CHECKED=0

for i in test/compiler/in/*.c; do
  echo "==========================="
  echo "Input file : ${i}"
  BASENAME=$(basename $i .c);
  mips-linux-gnu-gcc -S -O0 -static -o test/compiler/ref/$BASENAME $i
  
  
  cat $i | ./bin/c_compiler > test/compiler/out/$BASENAME.mips 2> test/compiler/out/$BASENAME.stderr.txt
  
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
  
