cmake_minimum_required(VERSION 3.10)



################################################################################
# The Project Name will the the name of the folder. Change it if you
# dont like it.
################################################################################
project( hello_world  CXX )
################################################################################

find_package(Python3 3.6.0 COMPONENTS Interpreter Development REQUIRED)

if( EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(NO_OUTPUT_DIRS TARGETS)
endif()

################################################################################
# Build the executable
#
################################################################################
set(outName              ${PROJECT_NAME})   # name of the library
set(srcFiles             "main.cpp"     )          # all the source files for this library
set(PublicLinkedTargets  ""             )
set(PrivateLinkedTargets  CONAN_PKG::spdlog CONAN_PKG::glm CONAN_PKG::nlohmann_json CONAN_PKG::catch2 Python3::Python CONAN_PKG::pybind11 )

#-------------------------------------------------------------------------------
file(GLOB_RECURSE srcFiles ${srcFiles} )
add_executable( ${outName} ${srcFiles} )

target_include_directories( ${outName}
                            PUBLIC
                               "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
 )

target_compile_features( ${outName}
                          PUBLIC
                              cxx_std_17)

target_compile_definitions( ${outName}
                                PUBLIC
                                TEST_DEFINE)

target_link_libraries( ${outName}  PUBLIC  ${PublicLinkedTargets}  )
target_link_libraries( ${outName}  PRIVATE ${PrivateLinkedTargets} )

################################################################################
