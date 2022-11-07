cmake_minimum_required(VERSION 3.10)



################################################################################
# The Project Name will the the name of the folder. Change it if you
# dont like it.
################################################################################
project( hello_world  CXX )
################################################################################

if( EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(NO_OUTPUT_DIRS TARGETS)
endif()

find_package(Threads)

################################################################################
# Build the executable
#
################################################################################
set(outName              server)   # name of the library
set(srcFiles             "server.cpp"     )          # all the source files for this library
set(PublicLinkedTargets  ""             )
set(PrivateLinkedTargets  CONAN_PKG::rpclib Threads::Threads)

#-------------------------------------------------------------------------------
file(GLOB_RECURSE srcFiles ${srcFiles} )
add_executable( ${outName} ${srcFiles} )

target_include_directories( ${outName}
                            PUBLIC
                               "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                               "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/rpclib/include>"
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



################################################################################
# Build the executable
#
################################################################################
set(outName              client)   # name of the library
set(srcFiles             "client.cpp"     )          # all the source files for this library
set(PublicLinkedTargets  ""             )
set(PrivateLinkedTargets  CONAN_PKG::rpclib Threads::Threads)

#-------------------------------------------------------------------------------
file(GLOB_RECURSE srcFiles ${srcFiles} )
add_executable( ${outName} ${srcFiles} )

target_include_directories( ${outName}
                            PUBLIC
                               "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                               "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/rpclib/include>"
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



