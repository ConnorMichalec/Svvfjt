cmake_minimum_required (VERSION 3.12) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "clang++")

project (Svvfjt)

add_subdirectory(src)

add_definitions(-D__LINUX_ALSA__)   # Otherwise stk won't know what driver to use and will fail to include pthread