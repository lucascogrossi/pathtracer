cmake_minimum_required(VERSION 3.18)

project(path_tracer LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CUDA settings
set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# RTX 5060 (Blackwell), compute capability 12.0
set(CMAKE_CUDA_ARCHITECTURES 120)

include_directories(include)

# CPU version
add_executable(main src/main.cpp)

# CUDA version
add_executable(cudart cuda/main.cu)
target_include_directories(cudart PRIVATE cuda)
