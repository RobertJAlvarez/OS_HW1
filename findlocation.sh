#!/bin/bash
if [ -z "$1" ] || [[ ! $1 =~ ^[[:digit:]]+$ ]]
then
  echo "Enter a North American phone number prefix with only the first 6 numbers"
  exit 1
fi

line=$( grep $1 nanpa )

if [ -z "$line" ]
then
  echo "Code didn't match a North American phone number prefix in nanpa."
  exit 1
fi

line=`echo $line | sed 's/ *$//'` ##Remove spaces after last character
line=`echo $line | sed "s/$1//"`  ##Remove phone number prefix
echo $line

