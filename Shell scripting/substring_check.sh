#!/bin/bash

# Function to count occurrences of a substring in a string
count_occurrences() {
    string="$1"
    substring="$2"

    # Use grep to find matches and then count the lines
    count=$(echo "$string" | grep -o "$substring" | wc -l)

    echo "Number of occurrences of '$substring' in '$string': $count"
}
count_occurrences "$1" "$2"
