#!/bin/bash

N=${N:-15}

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
        printf "%3d %s\n" "$sum" "$r"
    done
}

x_list="$(ls | grep '\.exe$')"

touch_n $x_list

run_n $x_list

res_sum | sort -n
