#!bin/bash

echo -n "Enter file name : "
read file_loc

# Check if File Exists
if [ ! -e $file_loc ]; then
    echo "File not found: $file_loc"
    exit 1
fi

# File type
file_type=$(file -b $file_loc)
echo "Type of file $file_loc is: $file_type"

# File permissions
[ -w $file_loc ] && W="1. Write = yes" || W="1. Write = No"
[ -x $file_loc ] && X="2. Execute = yes" || X="2. Execute = No"
[ -r $file_loc ] && R="3. Read = yes" || R="3. Read = No"

echo "Permissions for $file_loc are as follows:"
echo "$W"
echo "$R"
echo "$X"

