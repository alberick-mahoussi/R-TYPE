cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
#list(APPEND VCPKG_MANIFEST_FEATURES "rtype")

if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/asio")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/sfml")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share/pthread")
endif()

if(UNIX)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux/share/asio")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux/share/sfml")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux/share/pthread")
endif()

project("r-type" VERSION 0.1.0)

set(SOURCES_CLIENT
    src/Client/Initialization.cpp
    src/Client/Client.cpp
)

set(SOURCES_SERVER
    src/Server/main.cpp
    src/Server/Server.cpp
)

FILE(COPY assets DESTINATION ../build)

add_executable(r-type_client ${SOURCES_CLIENT})
add_executable(r-type_server ${SOURCES_SERVER})

find_package(SFML 2.5 COMPONENTS graphics network system window audio REQUIRED)
#find_package(asio CONFIG REQUIRED)

target_include_directories(r-type_client PRIVATE include/)
target_include_directories(r-type_server PRIVATE include/)

target_link_libraries(r-type_server PRIVATE pthread)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio pthread)