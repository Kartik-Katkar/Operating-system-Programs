#!/bin/bash

read -p "Enter the string to be checked: " input
reverse=""

len=${#input}
for (( i=$len-1; i>=0; i-- )); do
    reverse="$reverse${input:$i:1}"
done
if [ $input == $reverse ]; then
    echo "$input is a Palindrome."
else
    echo "$input is NOT a Palindrome."
fi

