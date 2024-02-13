##
## EPITECH PROJECT, 2023
## B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
## File description:
## build.window
##

#!/bin/bash

# Script spécifique à Windows (MSYS2)
mkdir build
cmake -G "Visual Studio 15 2017" -A x64 -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Release
