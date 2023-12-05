#!/bin/bash
echo "enter the number of element"
read n
i=0
while [ $i -lt $n ]
do
   read no[$i]
   i=`expr $i + 1`
done
for ((i = 0; i<n; i++)); do
  for ((j = 0; j<n-i-1; j++)); do
       if [ ${no[j]} -gt ${no[j+1]} ]; then
            temp=${no[j]}
            no[j]=${no[j+1]}
            no[j+1]=$temp
       fi
   done
done
#for ((i = 0; i < n; i++)); do
#    for ((j = 0; j < n - i - 1; j++)); do
#        if [ ${no[j]} -gt ${no[j+1]} ]; then
#            temp=${no[j]}
#            no[j]=${no[j+1]}
#            no[j+1]=$temp
#        fi
#    done
#done
echo "Array in sorted order :"
echo ${no[@]}
