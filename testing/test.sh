#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Je treba program spustit s parametrem ./../ifj";
    exit 1
fi


if [ "$1" != "./../ifj" ];then
    echo "Je treba spustit program nad prekladacem ifj! Parametr: \"./../ifj\"";
    exit 1
fi

runtest=$1
extension=".ifj16"
syntstring="synt"
synttests=1
date=`date +%y-%m-%d-%H-%M`
fileName="test_$date"
fileName="$fileName.txt"

	echo "=============================\n" > $fileName 
	echo "====== TEST RET HODNOT ======\n" > $fileName

while [ $synttests -le 7 ]; do
	synttest=$syntstring$synttests
	FILE=$synttest$extension
	synttest="$runtest $FILE DEBUG"

	$synttest 2>/dev/null;

	testResult=$?
	testResult=$((testResult+0))
	echo -e "FILE: $FILE" >> $fileName;
        if [ $testResult -eq 2 ]; then
                echo -e "RETVAL: $testResult; Test $synttests passed" >> $fileName;
        fi
        if [ $testResult -ne 2 ]; then
                echo -e "RETVAL: $testResult; Test $synttests failed" >> $fileName;
        fi

	synttests=$((synttests + 1))

done

semstring="sem"
semtests=1
while [ $semtests -le 46 ]; do
    semtest=$semstring$semtests
    FILE=$semtest$extension
    semtest="$runtest $FILE DEBUG"
	

    $semtest 2>/dev/null;


	testResult=$?
	testResult=$((testResult+0))
    echo -e "FILE: $FILE" >> $fileName;

	if [ $testResult -eq 3 ]; then
		echo -e "RETVAL: $testResult; Test $semtests passed" >> $fileName;
	fi
	if [ $testResult -ne 3 ]; then
		echo -e "RETVAL: $testResult; Test $semtests failed" >> $fileName;
	fi
	
    semtests=$((semtests + 1))

done

exit 0
