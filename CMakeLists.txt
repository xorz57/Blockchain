cmake_minimum_required(VERSION 3.24)

cmake_policy(SET CMP0091 NEW)

project(Blockchain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (VCPKG_TARGET_TRIPLET MATCHES "-static$")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)

set(SOURCES src/Main.cpp
            src/Block.cpp
            src/Blockchain.cpp
            src/Cryptography.cpp)

add_executable(Blockchain ${SOURCES})
target_link_libraries(Blockchain PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Blockchain PRIVATE OpenSSL::SSL)
