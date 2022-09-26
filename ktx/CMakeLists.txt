cmake_minimum_required(VERSION 3.16)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

################################################################################
# The Project Name will the the name of the folder. Change it if you
# dont like it.
################################################################################
project( ktxTranscodeTest )
################################################################################



################################################################################
# Make sure we include conan so that it can find
# all the packages
################################################################################
if( EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(NO_OUTPUT_DIRS TARGETS)
else()
    message(ERROR "No conanbuildinfo.cmake found in build directory.")
endif()

################################################################################



################################################################################

find_package(Ktx REQUIRED)
find_package(Threads REQUIRED)

################################################################################


 
################################################################################
# Build the executable
#
################################################################################
add_executable( ${PROJECT_NAME} ktxTranscodeTest.cpp )

target_include_directories( ${PROJECT_NAME}
                            PUBLIC
                               "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
 )

target_compile_features( ${PROJECT_NAME}
                          PUBLIC
                              cxx_std_17)

target_link_libraries( ${PROJECT_NAME}  PRIVATE KTX::ktx Threads::Threads)

################################################################################



