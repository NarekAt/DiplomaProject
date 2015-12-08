#!/bin/bash

for d in graph_test alternate_property_computer_test graph_generator_test
do
    ( cd $d && ./lib/*.exe )
done
