#! /bin/bash
# Test script for lab 3 which tested the database

DATABASE_INPUT_ARRAY=(in30.txt in33.txt in35.txt in36.txt in37.txt in41.txt in42.txt in43.txt in44.txt in61.txt in62.txt)
DATABASE_OUTPUT_ARRAY=(out30.txt out33.txt out35.txt out36.txt out37.txt out41.txt out42.txt out43.txt out44.txt out61.txt out62.txt)

echo "Testing Lab 3, Use a Relational Database to fill Schemes, Facts, and evaluate Queries"

for i in 0 1 2 3 4 5 6 7 8 9 10
do
    ./lab3 input_files_database/${DATABASE_INPUT_ARRAY[i]} > out.txt

    diff  out.txt output_files_database/${DATABASE_OUTPUT_ARRAY[i]} >/dev/null
    comp_value=$?

    if [ $comp_value -eq 1 ]
    then
        echo ${DATABASE_INPUT_ARRAY[i]} " is incorrect"
    else
        echo ${DATABASE_INPUT_ARRAY[i]} " is correct"
    fi
done
