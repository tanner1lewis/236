#! /bin/bash
# Test script for Lab 4 which tested the Rules

RULES_INPUT_ARRAY=(in40.txt in44.txt in45.txt in46.txt in47.txt in48.txt in49.txt in54.txt in55.txt in61.txt in62.txt)
RULES_OUTPUT_ARRAY=(out40.txt out44.txt out45.txt out46.txt out47.txt out48.txt out49.txt out54.txt out55.txt out61.txt out62.txt)

echo "Testing Lab 4, Rule evaluation"

for i in 0 1 2 3 4 5 6 7 8 9 10
do
    ./lab4 input_files_rules/${RULES_INPUT_ARRAY[i]} > out.txt

    diff  out.txt output_files_rules/${RULES_OUTPUT_ARRAY[i]} >/dev/null
    comp_value=$?

    if [ $comp_value -eq 1 ]
    then
        echo ${RULES_INPUT_ARRAY[i]} " is incorrect"
    else
        echo ${RULES_INPUT_ARRAY[i]} " is correct"
    fi
done
