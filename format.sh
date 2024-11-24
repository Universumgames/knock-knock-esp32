#!/bin/bash

scriptDir=$(dirname "$0")

# find files in any child dir in lib and src dir ending in .c, .h, .cpp, .hpp
filesToFormat=$(find "$scriptDir"/lib "$scriptDir"/src "$scriptDir"/test -type f -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp")

# loop through each file and run clang-format on it
for file in $filesToFormat; do
    clang-format -i "$file"
done