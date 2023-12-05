#!/bin/bash
avg()
{
read no
i=0
avg=0
while [ $i -lt $no ]
do
  read num
  avg=`expr ${num} + ${avg}`
  i=`expr ${i} + 1`
done
echo $avg
}
max()
{
read no
i=0
maxi=-1
while [ $i -lt $no ]
do
  read num
  if [ $num -gt $maxi ]
  then
    maxi=$num
  fi
  i=`expr ${i} + 1`
done
echo $maxi
}
min()
{
read no
i=0
mini=MAX_INT
while [ $i -lt $no ]
do
  read num
  if [ $num -lt $mini ]
  then
    mini=$num
  fi
  i=`expr ${i} + 1`
done
echo $mini
}
min
