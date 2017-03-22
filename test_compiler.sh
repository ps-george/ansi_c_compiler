#!/bin/bash

# Make compiler
#make clean
make bin/c_compiler

# make test results directory
mkdir -p test/compiler/out
mkdir -p test/compiler/ref
PASSED=0
CHECKED=0

for i in test/compiler/in/*.c; do
  
  BASENAME=$(basename $i .c);
  mips-linux-gnu-gcc -S -o test/compiler/ref/$BASENAME.s $i
  
  
  cat $i | ./bin/c_compiler > test/compiler/out/$BASENAME.s 2> test/compiler/out/$BASENAME.stderr.txt
  
  mips-linux-gnu-gcc -static test/compiler/out/$BASENAME.s -o test/compiler/out/$BASENAME
  mips-linux-gnu-gcc -static -O0 test/compiler/ref/$BASENAME.s -o test/compiler/ref/$BASENAME
  
  ./test/compiler/out/$BASENAME
  RESULT=$?
  
  ./test/compiler/ref/$BASENAME
  REF=$?
  
  
  if [[ $REF -ne $RESULT ]]; then
      echo "==========================="
      echo "Input file : ${i}"
      echo -e "\nERROR, expecting $REF but got $RESULT."
      echo "==========================="
  else
    if ! [ -z "$1" ]; then
      echo "==========================="
      echo "Input file : ${i}"
      echo -e "\nPASS, expecting $REF and got $RESULT."
    fi
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
  
