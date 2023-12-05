#!/bin/bash

if [ $# -eq 0 ]
then
  	echo "Please provide a file as a command-line argument."
  	exit 1
fi


if [ ! -e $1 ]
then
  	echo "File '$1' does not exist."
  	exit 1
fi

if [ -f $1 ]
then
  	file_type="Regular file"
elif [ -d $1 ]
then
 	file_type="Directory"
elif [ -c $1 ] 
then
	file_type="Character device file"
elif [ -L $1 ]
then
  	file_type="Symbolic link file"
elif [ -b $1 ] 
then
       	file_type="Blog device file"
fi


if [ -r $1 ]
then
	permissions=", Read"
fi

if [ -w $1 ]
then
	permissions+=", Write"
fi

if [ -x $1 ]
then
	permissions+=", Executable"
fi

echo "$1 is a $file_type"
echo "$1 has$permissions permissions"