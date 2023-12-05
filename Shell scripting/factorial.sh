#!/bin/bash

read -p "Enter the number of whose factorial you want: " n

factorial_without(){
    fact=1
    for ((i=1 ; i <= $n ; i++)); do
        fact=$(( $fact * $i ))
    done
    echo "Factorial of given number without recursion is: $fact"
}

factorial_recursion() {
    n=$1
    if [ $n -eq 0 ]; then
        echo 1
    else
        prev=`expr $n - 1`
        prev_fact=`factorial_recursion $prev`
        echo `expr $n \* $prev_fact`
    fi
#    echo "Factorial of given number with recursion is: $fact"
}

exiting() {
flag=1
exit 0
}

flag=0
while [ $flag -eq 0 ]
do
    echo -e "Menu:\n1. Without Recursion\n2. With Recursion\n3. Exit"
    read -p "Enter your choice: " ch

    case $ch in
        1) factorial_without $n ;;
        2) echo "Factorial of given number with recursion is:" `factorial_recursion $n`;;
        3) exiting ;;
        *) echo "Wrong choice" ;;
    esac
done

