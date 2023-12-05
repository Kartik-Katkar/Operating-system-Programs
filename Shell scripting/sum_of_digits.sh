#!/bin/bash

num=$1
sum=0
while [ $num != 0 ];
do
	digit=`expr $num % 10`
	sum=`expr $sum + $digit`
	num=`expr $num / 10`
done
echo "Sum of the digits is $sum"
