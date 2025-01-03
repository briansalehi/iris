cmake_minimum_required(VERSION 3.30)
project(Iris VERSION 0.3 LANGUAGES CXX DESCRIPTION "Automatic Screen Brightness Adjustment Utility")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INSTALL_RPATH $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>)

find_package(Boost 1.80.0 CONFIG COMPONENTS system program_options REQUIRED)

# build
file(GLOB source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
add_executable(adjust-brightness ${source_files})
target_include_directories(adjust-brightness PRIVATE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(adjust-brightness PRIVATE Boost::program_options)
target_compile_definitions(adjust-brightness PRIVATE -D PROGRAM_VERSION=${CMAKE_PROJECT_VERSION})

# test
enable_testing()

# install
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/AdjustBrightnessVersion.cmake COMPATIBILITY SameMajorVersion)
install(TARGETS adjust-brightness RUNTIME CONFIGURATIONS Release MinSizeRel)

# pack
set(CPACK_PACKAGE_VENDOR "Brian Salehi <briansalehi@proton.me>")
set(CPACK_PACKAGE_CONTACT "briansalehi@proton.me")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Packages)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-system-dev (>= 1.80.0), libboost-program-options-dev (>= 1.80.0)")
set(CPACK_RPM_PACKAGE_REQUIRES "boost-system >= 1.80.0, boost-program-options >= 1.80.0")
include(CPack)
