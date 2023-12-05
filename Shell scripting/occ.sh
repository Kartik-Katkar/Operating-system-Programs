#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <string> <substring>"
    exit 1
fi

main_string="$1"
substring="$2"

# Use grep to find all occurrences of the substring in the main string
# -o option is used to output only the matched parts of the string
# wc -l is then used to count the number of lines (occurrences)
occurrences=$(echo "$main_string" | grep -o "$substring" | wc -l)

echo "Number of occurrences of '$substring' in '$main_string': $occurrences"

