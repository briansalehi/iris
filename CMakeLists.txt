cmake_minimum_required(VERSION 3.15)
project("Adjust Brightness" VERSION 0.2 LANGUAGES CXX)

include(GNUInstallDirs)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INSTALL_RPATH $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>)
set(CPACK_PACKAGE_VENDOR "Brian Salehi")
set(CPACK_PACKAGE_CONTACT "briansalehi@proton.me")
set(CPACK_PACKAGE_DESCRIPTION "Terminal utility to adjust screen brightness")

find_package(Boost 1.80.0 CONFIG COMPONENTS system program_options REQUIRED)

add_executable(adjust-brightness src/main.cpp src/argument_parser.cpp)
target_sources(adjust-brightness PRIVATE include)
target_include_directories(adjust-brightness PRIVATE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(adjust-brightness PRIVATE Boost::program_options)
target_compile_definitions(adjust-brightness PRIVATE -D PROGRAM_VERSION=${CMAKE_PROJECT_VERSION})

install(TARGETS adjust-brightness EXPORT AdjustBrightnessTargets FILE_SET SOURCES CONFIGURATIONS Release)
