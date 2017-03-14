#!/bin/bash

destfile=doc/capabilities.txt
echo "Tested features:" > "$destfile"

for i in test/compiler/in/*.c; do
  
  line=$(head -n 1 $i)
  echo "$line" >> "$destfile"
  
done
  
