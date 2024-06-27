cmake_minimum_required(VERSION 3.24)

cmake_policy(SET CMP0091 NEW)

project(Blockchain)

if (VCPKG_TARGET_TRIPLET MATCHES "-static$")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

find_package(OpenSSL REQUIRED)

add_executable(Blockchain src/Main.cpp src/Block.cpp src/Blockchain.cpp src/Cryptography.cpp)
target_link_libraries(Blockchain PRIVATE OpenSSL::SSL)
target_compile_features(Blockchain PRIVATE cxx_std_20)
