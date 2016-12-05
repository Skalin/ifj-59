#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Je treba program spustit s parametrem ./../ifj";
    exit 1
fi


if [ "$1" != "./../ifj" ];then
    echo "Je treba spustit program nad prekladacem ifj! Parametr: \"./../ifj\"";
    exit 1
fi


date=`date +%y-%m-%d-%H-%M`
fileName="test_$date"
fileName="$fileName.txt"


	echo "=============================" >> $fileName;
        echo "====== TEST RET HODNOT ======" >> $fileName;

runtest=$1
extension=".ifj16"
FILE="lex1$extension"
	
lexttest="$runtest $FILE";

	$lexttest 2>/dev/null;

	testResult=$?
	testResult=$((testResult+0))
	echo -e "FILE: $FILE" >> $fileName;
	if [ $testResult -eq 99 ]; then
		echo -e "RETVAL: $testResult; Test $FILE passed" >> $fileName;
	else 
		echo -e "RETVAL: $testResult; Test $FILE failed" >> $fileName;
	fi

syntstring="synt"
synttests=1

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

echo "Vysledek testy byl ulozen do $fileName, pro vypis jeho obsahu pouzijte prikaz cat $fileName";

exit 0
