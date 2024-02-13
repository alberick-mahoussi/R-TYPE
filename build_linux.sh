##
## EPITECH PROJECT, 2023
## B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
## File description:
## build
##

#!/bin/bash

# Script spécifique à Linux
mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release

cmake --build .