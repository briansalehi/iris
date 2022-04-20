cmake_minimum_required(VERSION 3.15)
project("Adjust Brightness" VERSION 0.1 LANGUAGES CXX)

find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB SOURCE_FILES src/*.cxx)
add_executable(adjust-brightness ${SOURCE_FILES})
target_link_libraries(adjust-brightness PRIVATE Boost::program_options)
