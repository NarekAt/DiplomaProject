#!/bin/bash

GRAPH=$2
if [ -z "$GRAPH" ]
  then
      GRAPH=512
fi

if [ -z "$1" ]
  then
      time ./lib/graph_analyzer.exe -triangles ../install/boost_graphs/graph__N${GRAPH}_p0.3.txt
  else
      time mpirun -n ${1} ./lib/graph_analyzer.exe -triangles ../install/boost_graphs/graph__N${GRAPH}_p0.3.txt
fi
