#!/bin/bash

LOCATION=./valid_files/*.s
FILECOUNT=0
DIRCOUNT=0

rm ./valid_files/*.t ./valid_files/*.txt

if [ "$#" -lt "1" ]
then
    echo "Usage: ./test2.sh <directory>"
    exit 0
fi

#echo "The said files: " $LOCATION
for item in $LOCATION
do
if [ -f "$item" ]
then
	FILECOUNT=$[$FILECOUNT+1]
elif [ -d "$item" ]
then
 	DIRCOUNT=$[$DIRCOUNT+1]
fi
done

echo "File count: " $FILECOUNT
echo "Directory count: " $DIRCOUNT

for item in $LOCATION
do
if [ -e asm ]
then
	./asm $item
else
	make
fi
done

NEWFILES=*.cor
i=0

#echo "Cor files: " $NEWFILES

for file in $NEWFILES
do
	((i++))
	hexdump -C $file > ./valid_files/$i.txt
	#echo "Hexdump file done:" $i.txt
done
rm *.cor

for item in $LOCATION
do
	./zaz $item >&-
done

ZAZFILES=./valid_files/*.cor
var=0

for file in $ZAZFILES
do
	((var++))
	hexdump -C $file > ./valid_files/$var.t
	#echo "Hexdump file done:" $var.t
done
rm ./valid_files/*.cor

ZAZF=./valid_files/*.t
MYF=./valid_files/*.txt
res=0

set $MYF
for cmp in $ZAZF
do
	#diff $cmp $1
	if [ -e $(diff "$cmp" "$1") ]
	then
		echo "If nothing writen above : \x1B[32m[SUCCESS]\x1B[0m "$cmp $1
	else
		echo "Problem with the output : \x1B[31m[FAIL]\x1B[0m "$cmp $1
	fi
	shift
done
