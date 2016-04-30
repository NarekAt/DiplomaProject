#!/bin/bash

config=$1
processCount=$(xmllint --xpath 'count(//config/graphs/graph-path)' $config)
autoDetectCommunities=$(xmllint --xpath 'string(//config/auto-detect-communities)' $config)

red=`tput setaf 1`
reset=`tput sgr0`

function run {
    if [ ! -f ./alternate_property_computer.exe ]; then
        echo "${red}alternate_property_computer.exe not found in working directory${reset}"
    else
        if [ $autoDetectCommunities -eq 1 ] && [ $processCount -ne 1 ]; then
            echo "${red}Communities auto-detection works for single graph file${reset}"
            exit
        fi
        mpirun -np $processCount ./alternate_property_computer.exe $config
    fi
}

run
