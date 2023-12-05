#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

input_file=$1
even_file="even_numbers.txt"
odd_file="odd_numbers.txt"

# Check if input file exists
if [ ! -e $input_file ]; then
    echo "Input file not found: $input_file"
    exit 1
fi

# Clear existing output files or create new ones
> $even_file
> $odd_file

# Read each number from the input file and categorize into even or odd
while read -r number; do
    if [ $((number % 2)) -eq 0 ]; then
        echo $number >> $even_file
    else
        echo $number >> $odd_file
    fi
done < $input_file

echo "Even numbers saved in $even_file"
echo "Odd numbers saved in $odd_file"

