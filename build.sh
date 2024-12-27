#!/bin/bash

OPENSSLDIR="/c/Program Files/OpenSSL-Win64/"

COMPILE_FLAGS="-O3 -march=native -ffast-math -funroll-loops -flto -mavx2"
COMPILE_DEBUG="-g -O0"

compile()
{
    for c in $@; do
        #Windows
        gcc -I"$INCLUDE" -I"${OPENSSLDIR}include" -L"$LIB" -L"${OPENSSLDIR}" \
            $COMPILE_FLAGS \
            -o "${c%.*}" "$c" -lcrypto -lbutil
    done
}

args=()
while [[ $# -gt 0 ]]; do
    case "$1" in
        -h|--help)
            echo "usage: $0 [-d | --debug] [-h | --help] file.c ..."
            exit 0
            ;;
        -d|--debug)
            COMPILE_FLAGS="$COMPILE_DEBUG"
            ;;
        -*)
            echo "Invalid option: $1" >&2
            echo 'Try "$0 --help" for more information.' >&2
            exit 1
            ;;
        *)
            args+=("$1")  # Collect non-flag arguments
            ;;
    esac
    shift
done

if [[ ${#args[@]} -eq 0 ]]; then
    echo "No source files provided"
    exit 0
fi

compile "${args[@]}"
