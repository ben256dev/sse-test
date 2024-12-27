#!/bin/bash

OPENSSLDIR="/c/Program Files/OpenSSL-Win64/"

compile()
{
    #Windows
    gcc -I"$INCLUDE" -I"${OPENSSLDIR}include" -L"$LIB" -L"${OPENSSLDIR}" \
        -O3 -march=native \
        -o "${c:0:-2}" "$1" -lcrypto -lbutil
}

for c in $(ls | grep '\.c$'); do
    compile $c
done
