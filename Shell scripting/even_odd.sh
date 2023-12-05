#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

input_file="$1"
even_file="even_numbers.txt"
odd_file="odd_numbers.txt"

# Check if the input file exists
if [ ! -e "$input_file" ]; then
    echo "Error: Input file '$input_file' not found."
    exit 1
fi

# Clear existing output files
> "$even_file"
> "$odd_file"

# Read numbers from the input file and divide them into even and odd
while read -r number; do
    if [ $((number % 2)) -eq 0 ]; then
        echo $number >> "$even_file"
    else
        echo $number >> "$odd_file"
    fi
done < "$input_file"

echo "Even numbers stored in '$even_file'"
echo "Odd numbers stored in '$odd_file'"
