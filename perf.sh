#!/bin/bash

N=${N:-10}

touch_n()
{
    for n in $@; do
        >"${n:0:-3}res"
    done
}

run()
{
    ./"$1" >>"${1:0:-3}res"
}

run_n()
{
    for n in $(seq $N); do
        for x in $@; do run $x; done
    done
}

res_sum()
{
    for r in $(ls | grep '\.res$'); do
        sum=$(awk '{sum += $1} END { print sum}' "$r")
        printf "%7dus %s\n" "$sum" "$r"
    done
}

x_list="$(ls | grep '\.exe$') gl_v3_add.exe"

touch_n $x_list

run_n $x_list

res_sum | sort -n
