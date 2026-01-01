cmake_minimum_required(VERSION 3.28)
project(ocb-cpp-utils LANGUAGES CXX)

include(GNUInstallDirs)

add_library(ocb-cpp-utils INTERFACE)

target_include_directories(
    ocb-cpp-utils INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

target_compile_features(ocb-cpp-utils INTERFACE cxx_std_23)

find_package(Boost CONFIG REQUIRED)
target_link_libraries(ocb-cpp-utils INTERFACE Boost::boost)
