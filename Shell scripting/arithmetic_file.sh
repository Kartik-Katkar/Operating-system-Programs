#!/bin/bash

# Arithmetic operations
result_add=$((5 + 3))
result_sub=$((10 - 4))
result_mul=$((6 * 2))
result_div=$((20 / 4))

# Store output in a file
echo "Addition: $result_add" > arithmetic_output.txt
echo "Subtraction: $result_sub" >> arithmetic_output.txt
echo "Multiplication: $result_mul" >> arithmetic_output.txt
echo "Division: $result_div" >> arithmetic_output.txt

echo "Arithmetic operations completed. Output stored in arithmetic_output.txt."
