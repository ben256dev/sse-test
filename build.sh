#!/bin/bash

OPENSSLDIR="/c/Program Files/OpenSSL-Win64/"

for c in $(ls | grep '\.c$'); do
    #Windows
    gcc -I"$INCLUDE" -I"${OPENSSLDIR}include" -L"$LIB" -L"${OPENSSLDIR}" \
        -O3 -march=native -ffast-math -funroll-loops -flto -mavx2 \
        -o "${c:0:-2}" "$c" -lcrypto -lbutil
done
