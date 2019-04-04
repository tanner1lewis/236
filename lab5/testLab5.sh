#! /bin/bash
# Test script for Lab 4 which tested the Rules

GRAPH_INPUT_ARRAY=(in50.txt in54.txt in55.txt in56.txt in58.txt in59.txt in61.txt in62.txt in64.txt)
GRAPH_OUTPUT_ARRAY=(out50.txt out54.txt out55.txt out56.txt out58.txt out59.txt out61.txt out62.txt out64.txt)

echo "Testing Lab 5, Graph optimization"

for i in 0 1 2 3 4 5 6 7 8
do
    ./lab5 input_files_graph/${GRAPH_INPUT_ARRAY[i]} > out.txt

    diff  out.txt output_files_graph/${GRAPH_OUTPUT_ARRAY[i]} >/dev/null
    comp_value=$?

    if [ $comp_value -eq 1 ]
    then
        echo ${GRAPH_INPUT_ARRAY[i]} " is incorrect"
    else
        echo ${GRAPH_INPUT_ARRAY[i]} " is correct"
    fi
done
