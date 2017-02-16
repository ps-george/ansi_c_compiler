#!/bin/bash

# Make lexer
make clean
make bin/c_lexer

# make test files
mkdir -p test/lexer/in

# make test results directory
mkdir -p test/lexer/out
PASSED=0
CHECKED=0
# iterate through in directory
for i in test/lexer/in/*.c; do
  echo "==========================="
  echo "Input file : ${i}"
  BASENAME=$(basename $i .c);
  # Preprocess the files and pass output into c_lexer
  cat $i | ./bin/c_lexer > test/lexer/out/$BASENAME.stdout.txt 2> test/lexer/out/$BASENAME.stderr.txt
  cat test/lexer/out/$BASENAME.stdout.txt | jq . > test/lexer/out/$BASENAME.json.txt
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
