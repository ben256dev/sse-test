#!/bin/bash

if [[ $# -eq 0 ]]; then
    echo "usage: $0 0...(vector count)"
    exit 0
fi

vector_count=$1

odd=$(expr $vector_count % 2)
if [ $odd -eq 1 ]; then 
    echo "vector count must be even!"
    exit 0
fi

>spec.$vector_count
let vectors_bytes="3*4*vector_count"
openssl rand $vectors_bytes >>spec.$vector_count
echo "wrote $vectors_bytes bytes to \"spec.$vector_count\""
