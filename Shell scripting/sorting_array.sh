#!bin/bash

read -p "Enter the number of elements you wish to work with: " n
echo "Enter the numbers: "

for ((i = 0; i < n; i++)); do
    read array[$i]
done

for ((i = 0; i < n; i++)); do
    for ((j = 0; j < n-i-1; j++)); do
        if [ ${array[j]} -gt ${array[$((j+1))]} ]
        then
            #swapping
            temp=${array[j]}
            array[$j]=${array[$((j+1))]}
            array[$((j+1))]=$temp
        fi
    done
done

echo "The sorted array is: ${array[*]}"

