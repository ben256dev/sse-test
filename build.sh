#!/bin/bash

OPENSSLDIR="/c/Program Files/OpenSSL-Win64/"

for c in $(ls | grep '\.c$'); do
    gcc -I"$INCLUDE" -I"${OPENSSLDIR}include" -L"$LIB" -L"${OPENSSLDIR}" -o "${c:0:-2}" "$c" -lcrypto -lbutil
done
