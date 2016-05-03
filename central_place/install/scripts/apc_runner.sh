#!/bin/bash

config=$1
graphCount=$(xmllint --xpath 'count(//config/graphs/graph-path)' $config)
maxProcCount=$(xmllint --xpath 'number(//config/max-parallel-proc-count)' $config)
calculateAvg=$(xmllint --xpath 'string(//config/calculate-average)' $config)
communityGraph=$(xmllint --xpath 'string(//config/community-graph)' $config)

red=`tput setaf 1`
reset=`tput sgr0`

function run {
    if [ ! -f ./alternate_property_computer.exe ]; then
        echo "${red}alternate_property_computer.exe not found in working directory${reset}"
    else
        fromIndex=0
        while [ $graphCount -gt 0 ]; do
            if [ $graphCount -gt $maxProcCount ]; then
                processCount=$maxProcCount
            else
                processCount=$graphCount
            fi
            graphCount=$(( $graphCount - $maxProcCount ))
            
            mpirun -np $processCount ./alternate_property_computer.exe $config $fromIndex
            
            fromIndex=$(( $fromIndex + $maxProcCount ))
        done
        [ "$calculateAvg" = "true" ] || [ "$calculateAvg" = "1" ] && ./avg_calc.sh
    fi
}

run

# Rest of the script is written for community detection

function removeTag {
    fileName=$1
    tagName=$2
    
    xmlstarlet ed -d "//$tagName" $fileName > temp.xml
    mv temp.xml $fileName
}

function addTag {
    fileName=$1
    parentTagName=$2
    tagName=$3
    content=$4
    
    xmlstarlet ed -s "//$parentTagName" -t elem -n $tagName -v $content $fileName > temp.xml
    mv temp.xml $fileName    
}

function generateAndRun {
    communityConfigPath="./community_graphs/community.xml"
    
    # Generating graphs
    ./community_detector.exe $communityGraph
    
    # Creating new config file
    cp $config $communityConfigPath
    
    # Removing graphs and communityGraph
    removeTag $communityConfigPath "graph-path"
    removeTag $communityConfigPath "community-graph"
    
    # Adding generated graphs to file
    paths=($(find ./community_graphs/ -name "community_graph*txt" -type f -printf "%f\n"))
    
    for (( i = 0; i < ${#paths[@]}; i++ )); do
        addTag $communityConfigPath "graphs" "graph-path" ${paths[i]}
    done
    
    # Hamadzayn em tapor lucum a
    cp apc_runner.sh community_graphs
    cp avg_calc.sh community_graphs
    cp alternate_property_computer.exe community_graphs
    
    (cd community_graphs && ./apc_runner.sh community.xml && cd ../) 
}

[ ! -z $communityGraph ] && generateAndRun
