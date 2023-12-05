#!/bin/bash

read -p "Enter the number of elements you wish to work with: " n
echo "Enter the numbers: "

for ((i = 0; i < n; i++)); do
    read array[$i]
done

average() {
    arr=("$@")
    num=${#arr[@]}
    sum=0
    for i in "${arr[@]}"; do
        sum=$((sum + i))
    done

    avg=$(awk "BEGIN {printf \"%.2f\", $sum / $num}")
    echo "Average of given numbers is: $avg"
}

minimum() {
    arr=("$@")
    min=${arr[0]}
    for i in "${arr[@]}"; do
        if [[ $i -lt $min ]]; then
            min=$i
        fi
    done

    echo "Minimum number amongst the given numbers is: $min"
}

maximum() {
    arr=("$@")
    max=${arr[0]}
    for i in "${arr[@]}"; do
        if [[ $i -gt $max ]]; then
            max=$i
        fi
    done

    echo "Maximum number amongst the given numbers is: $max"
}

exiting() {
flag=1
exit 0
}

flag=0
while [ $flag -eq 0 ] 
do
	echo -e "Menu:\n1. Average\n2. Maximum\n3. Minimum\n4. Exit"
	read -p "Enter your choice: " ch

	case $ch in
	    1) average "${array[@]}" ;;
	    2) maximum "${array[@]}" ;;
	    3) minimum "${array[@]}" ;;
	    4) exiting ;;
	    *) echo "Wrong choice" ;;
	esac
done

