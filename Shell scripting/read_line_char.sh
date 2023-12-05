#!/bin/bash

# Function to read the file line by line
read_file_line_by_line() {
    while IFS= read -r line; do
        echo "Line: $line"
    done < "$1"
}

# Function to read the file character by character
read_file_char_by_char() {
    while read -r -n1 char; do
        echo "Character: $char"
    done < "$1"
}

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file=$1

if [ ! -e "$file" ]; then
    echo "File not found: $file"
    exit 1
fi

echo "Reading file line by line:"
read_file_line_by_line "$file"

echo "Reading file character by character:"
read_file_char_by_char "$file"

