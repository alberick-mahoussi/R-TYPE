# R-TYPE

<a href="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" alt="SFML">
        <img src="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" alt="C++">
        <img src="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" alt="Cmake">
        <img src="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" /></a>

A 3rd year Epitech Project

The goal is to implement a multithreaded server and a graphical client for a well-known legacy video game
called R-Type, using a game engine of our own design

## Installation

You MUST have g++ and CMake installed on your operating system

### Setting up vcpkg

```sh
git submodule init
```
```sh
git submodule update
```

### Creating the executable

```sh
mkdir build && cd build
```
#### For Windows
```sh
cmake .. -G "Visual Studio 15 2017" -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
```
```sh
cmake --build . --config Release
```
#### For Linux
```sh
cmake .. -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
```
```sh
cmake --build .
```

## Contributors

* sean.jaboulet@epitech.eu
* pascal.lin@epitech.eu
* alberick.mahoussi@epitech.eu
* miles-alexandre-nicholas1.tonye-mbog@epitech.eu
* aurelien.lenfant@epitech.eu

## License
[MIT](https://choosealicense.com/licenses/mit/)