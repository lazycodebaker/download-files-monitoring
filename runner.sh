#!/bin/bash

g++ -std=c++17 -framework CoreServices -o main ./test.cpp

if [ $? -eq 0 ]; then
    ./main
else
    echo "Compilation failed."
fi
