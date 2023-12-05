#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

# Read file line by line
echo "Reading file line by line:"
while IFS= read -r line; do
    echo "Line: $line"
done < "$filename"

# Read file character by character
echo -e "\nReading file character by character:"
while IFS= read -n 1 char; do
    echo "Character: $char"
done < "$filename"

echo "File reading complete."

