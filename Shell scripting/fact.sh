#!/bin/bash
fac()
{
num=$1
fact=1
for ((i=1;i<=$num;i++))
do
  fact=`expr ${i} \* ${fact}`
done
echo $fact
}
fac_rec()
{
if [ $1 -le 1 ]
then
    return 1
else
   a=`expr $1 - 1`
   fac_rec $a
   b=`expr $1 \* $?`
   return $b
fi
}
fac_rec $1
echo $?
