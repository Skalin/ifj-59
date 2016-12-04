#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Je treba program spustit s parametrem ./ifj16";
    exit 1
fi

echo $1;

exit 0