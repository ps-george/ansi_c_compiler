#!/bin/bash

destfile=doc/capabilities.txt
echo "Tested features:" > "$destfile"
k=1
for i in test/compiler/in/*.c; do
  remove="//"
  line=$(head -n 1 $i)
  echo -e "$k.\t${line#"$remove"}" >> "$destfile"
  ((k++))
done
  
