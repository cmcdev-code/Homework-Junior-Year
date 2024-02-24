#!/usr/bin/env bash


mkdir "${1}_calendar"

cd "${1}_calendar"


for i in {1..12}
do
    mkdir Month$(printf "%02d" $i)
    cd Month$(printf "%02d" $i)
    days=31

    case $i in
        2)
            days=28
            ;;
        4|6|9|11)
            days=30
            ;;
    esac

    for j in $(seq 1 $days)
    do
        touch Day$(printf "%02d" $j).txt
    done

    cd ..
done
