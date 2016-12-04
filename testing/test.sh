#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Je treba program spustit s parametrem ./ifj16";
    exit 1
fi


if [ "$1" != "./ifj16" ];then
    echo "Je treba spustit program nad prekladacem ifj16!";
    exit 1
fi

runtest=$1

extension=".ifj16"
semstring="sem"
semtests=1
while [ $semtests -le 46 ]; do
    semtest=$sem$semtests
    semtest="$runtest $semtest$extension"
    semtests=$((semttests + 1))

    $semtest;


    printf $?;

done

exit 0