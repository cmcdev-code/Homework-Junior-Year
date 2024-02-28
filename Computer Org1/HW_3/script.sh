#!/usr/bin/env bash


# Creating the directory with what the user entered when running the shell script
mkdir $1_calendar

# Switching to directory that was created
cd $1_calendar


for i in {1..12};
do 
    #Creating the 12 months
    mkdir Month$(printf "%02d" $i)

    #Logic to check which month and assign correct number of days to said month
    if [[ $i -ne 2 ]] && [[ $i -ne 4 ]] && [[ $i -ne 6 ]] && [[ $i -ne 9 ]] && [[ $i -ne 11 ]]; then
        touch Month$(printf "%02d" $i)/Day{01..31}.txt
    elif [[ $i = 2 ]]; then
        touch Month$(printf "%02d" $i)/Day{01..28}.txt
    else 
        touch Month$(printf "%02d" $i)/Day{01..30}.txt
    fi

done
