#!/bin/bash
read str
str2=""
i=${#str}
arr[5]
while [ $i -ge 0 ]
do
    str3=${str:$i:1}
    arr[$i]=$str3
    echo $str3
   str2=$str2${str:$i:1}
   i=`expr $i - 1`
done
echo $str2
echo ${arr[@]}
