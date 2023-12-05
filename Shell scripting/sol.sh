#!/bin/bash

# Check if the correct number of arguments is provided
if [ $# -ne 3 ]; then
    echo "Usage: $0 <operand1> <operator> <operand2>"
    exit 1
fi

# Assign command line arguments to variables
operand1=$1
operator=$2
operand2=$3

# Perform arithmetic operation
result=0

case $operator in
    "+")
        result=$((operand1 + operand2))
        ;;
    "-")
        result=$((operand1 - operand2))
        ;;
    "*")
        result=$((operand1 * operand2))
        ;;
    "/")
        if [ "$operand2" -eq 0 ]; then
            echo "Error: Division by zero is not allowed."
            exit 1
        fi
        result=$(echo "scale=2; $operand1 / $operand2" | bc)
        ;;
    *)
        echo "Error: Invalid operator. Supported operators are +, -, *, /"
        exit 1
        ;;
esac

# Print the result to the console
echo "Result: $result"

# Store the result in a file
echo "Result: $result" > result.txt
echo "Result stored in 'result.txt'"
