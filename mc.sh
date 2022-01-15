#!/bin/bash

echo "min, max, avg" > out.csv
echo "date" > date.csv
g++ mc.cpp
for (( i=1000; i<=10000; i+=1000 ))
do
    date +"%Y-%m-%d %T" >> date.csv
    date +"%Y-%m-%d %T"
    echo Calculating $i
    ./a.out $i 25 >> out.csv
    mv valsout.txt vals.txt
	mv ptsout.txt pts.txt
    mv infout.txt inf.txt
done
date +"%Y-%m-%d %T" >> date.csv
date +"%Y-%m-%d %T"
echo Done.
rm vals.txt pts.txt inf.txt
