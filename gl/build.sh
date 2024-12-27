#!/bin/bash

OPENSSLDIR="/c/Program Files/OpenSSL-Win64/"

#Windows
gcc -I"$INCLUDE" -I"${OPENSSLDIR}include" -L"$LIB" -L"${OPENSSLDIR}" \
    -O3 -march=native \
    -o gl_v3_add.exe gl/gl_v3_add.c -lbutil -lglad -lglfw3 -lopengl32 -lgdi32 -lcrypto
