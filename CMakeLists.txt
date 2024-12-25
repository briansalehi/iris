cmake_minimum_required(VERSION 3.15)
project(adjust-brightness VERSION 0.2 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

enable_testing()

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

# install
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/AdjustBrightnessConfig.cmake "include(\${CMAKE_CURRENT_LIST_DIR}/AdjustBrightnessTargets.cmake)\n")
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/AdjustBrightnessVersion.cmake COMPATIBILITY SameMajorVersion)

install(TARGETS adjust-brightness EXPORT AdjustBrightnessTargets RUNTIME CONFIGURATIONS Release MinSizeRel)
install(EXPORT AdjustBrightnessTargets NAMESPACE AdjustBrightness:: CONFIGURATIONS Release MinSizeRel DESTINATION ${CMAKE_INSTALL_LIBDIR}/adjust-brightness/cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/AdjustBrightnessConfig.cmake CONFIGURATIONS Release MinSizeRel DESTINATION ${CMAKE_INSTALL_LIBDIR}/adjust-brightness/cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/AdjustBrightnessVersion.cmake CONFIGURATIONS Release MinSizeRel DESTINATION ${CMAKE_INSTALL_LIBDIR}/adjust-brightness/cmake)

# pack
set(CPACK_PACKAGE_VENDOR "Brian Salehi")
set(CPACK_PACKAGE_CONTACT "briansalehi@proton.me")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Terminal utility to adjust screen brightness")
set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")

list(APPEND CPACK_DEBIAN_PACKAGE_DEPENDS libboost-program-options-dev)

include(CPack)

