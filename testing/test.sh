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
semstring="sem"
semtests=1
while [ $semtests -le 46 ]; do
    semtest=$semstring$semtests
    semtest="$runtest $semtest$extension"
    semtests=$((semtests + 1))
    semtest="$semtest DEBUG"

    $semtest;


    printf $?;

done

exit 0