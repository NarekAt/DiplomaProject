#!/usr/bin/env bash


# Pattern as first argument
function getFilePaths {
    filePattern=$1
    
    paths=$(find ./global_results | grep "$filePattern")
    
    echo ${paths[@]}
}

function calculateAverage {
    filePattern=$1
    # This is done to store result in an array (...)
    paths=($(getFilePaths $filePattern))
    
    numberOfFiles=${#paths[@]}
    
    results=()
    for (( i = 0; i < $numberOfFiles; i++ )); do
        readarray fileArr < ${paths[i]}
        
        for (( j = 0; j < ${#fileArr[@]}; j++ )); do
            keyVal=(${fileArr[$j]}) # (...) operator splits string by spaces
            key=${keyVal[0]}
            val=${keyVal[1]}
            
            [ ${results[$key]+exists} ] && results[$key]=$(( ${results[$key]} + $val )) || results[$key]=$val
            [ $i -eq $(( $numberOfFiles - 1 )) ]  && results[$key]=$(( ${results[$key]} / $numberOfFiles ))
        done
    done
    
    echo ${results[@]}
}

function writeResults {
    results=("${!1}")
    path=$2
    fileName=$3
    
    
    mkdir -p $path
    touch $path/$fileName
    
    for key in "${!results[@]}"; do
        echo "$key ${results[$key]}" >> $path/$fileName
    done
}

results=($(calculateAverage "degree"))

writeResults results[@] "global_results/average_results" "degree.txt"

# mapfile readarray