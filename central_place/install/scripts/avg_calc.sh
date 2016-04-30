#!/usr/bin/env bash

red=`tput setaf 1`
reset=`tput sgr0`


# $1 Pattern with which to perform search
function getFilePaths {
    filePattern=$1
    
    # One does not simply stops bash execution
    # https://s-media-cache-ak0.pinimg.com/736x/76/a2/3d/76a23dcfc2350c57624d476b85593b58.jpg
    # [ ! -d ./global_results ] && echo "${red}Directory global_results not found!${reset}" && exit 1
    
    paths=$(find ./global_results | grep "$filePattern")
    
    # Nothing found
    [ -z "${paths[@]}" ] && return 0
    # [ -z "(find ./global_results | grep $filePattern)" ] && return 0
    
    echo ${paths[@]}
}

# $1 Pattern with which to perform search
function calculateAverage {
    filePattern=$1
    # This is done to store result in an array (...)
    paths=($(getFilePaths $filePattern))
    
    [ -z $paths ] && return 0
    
    numberOfFiles=${#paths[@]}
    
    results=()
    for (( i = 0; i < $numberOfFiles; i++ )); do
        mapfile fileArr < ${paths[$i]}
        
        for (( j = 0; j < ${#fileArr[@]}; j++ )); do
            keyVal=(${fileArr[$j]}) # (...) operator splits string by spaces
            key=${keyVal[0]}
            val=${keyVal[1]}
            
            # bc command is used to be able to perform operations on floating point numbers
            
            [ ${results[$key]+exists} ] && results[$key]=`bc -l <<< "${results[$key]} + $val"` || results[$key]=$val
            [ $i -eq $(( $numberOfFiles - 1 )) ]  && results[$key]=`bc -l <<< "${results[$key]} / $numberOfFiles"`
        done
    done
    
    echo ${results[@]} 
}

# $1 Result array
# $2 Directory path
# $3 File name
function writeResults {
    results=("${!1}")
    path=$2
    fileName=$3
    
    
    mkdir -p $path
    touch $path/$fileName
    
    for key in "${!results[@]}"; do
        # first expression removes all unnecessary zeros from the end, second adds 0 to numbers which begin with dot
        results[$key]=$(sed -e '/\./ s/\.\{0,1\}0\{1,\}$//' -e 's/\.\(.*\)$/0.\1/' <<< "${results[$key]}")
        echo "$key ${results[$key]}" >> $path/$fileName
    done
}

# degree
results=($(calculateAverage "degree"))
[ -z $results ] || writeResults results[@] "global_results/average_results" "degree.txt"

# betweenness_centrality
results=($(calculateAverage "betweenness_centrality"))
[ -z $results ] || writeResults results[@] "global_results/average_results" "betweenness_centrality.txt"

# eigenvector_centrality
results=($(calculateAverage "eigenvector_centrality"))
[ -z $results ] || writeResults results[@] "global_results/average_results" "eigenvector_centrality.txt"
