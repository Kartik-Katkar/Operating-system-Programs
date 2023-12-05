#!/bin/bash
echo "enter the number"
read no
n=$no
sum=0
i=0
len=${#n}
for((i=0;i<len;i++))
do
  d=`expr $n % 10`
  sum=`expr $sum + $d`
  n=`expr $n / 10`
done
echo $sum
