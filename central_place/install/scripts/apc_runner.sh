#!/bin/bash

config=$1
processCount=$(xmllint --xpath 'count(//config/graphs/graph-path)' $config)

red=`tput setaf 1`
reset=`tput sgr0`

function run {
    if [ ! -f ./alternate_property_computer.exe ]; then
        echo "${red}alternate_property_computer.exe not found in working directory${reset}"
    else
        mpirun -np $processCount ./alternate_property_computer.exe $config
    fi
}

run
