cmake_minimum_required(VERSION 3.5.0)
project(utils)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost COMPONENTS container_hash functional)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()