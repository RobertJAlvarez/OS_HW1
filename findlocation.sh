#!/bin/bash
if [ -z "$1" ] || [ 1000000 -lt $1 ] || [ 100000 -gt $1 ]
then
  for value in {0..9}
  do
    echo -n $value
  done
  echo
  exit 1
fi

line=$( grep $1 nanpa )

if [ -z "$line" ]
then
  echo "Code didn't match an North American phone number prefix in nanpa."
  exit 1
fi

line=`echo $line | sed 's/ *$//'` ##Remove spaces after last character
line=`echo $line | sed "s/$1//"`  ##Remove phone number prefix
echo $line

