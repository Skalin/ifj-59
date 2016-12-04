#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Je treba program spustit s parametrem ./ifj16";
    exit 1
fi


if [ "$1" == "./ifj16" ];then
    echo "Je treba spustit program nad prekladacem ifj16!";
    exit 1
fi

exit 0