cmake_minimum_required(VERSION 3.10)

################################################################################
# The Project Name will the the name of the folder. Change it if you
# dont like it.
################################################################################
project( hello_world )
################################################################################


################################################################################
# Build the executable
#
################################################################################
set(outName              ${PROJECT_NAME})   # name of the library
set(srcFiles             "main.cpp"     )          # all the source files for this library
set(PublicLinkedTargets  ""             )
set(PrivateLinkedTargets ""             )
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

target_precompile_headers(${PROJECT_NAME} PRIVATE
#  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/cxx_only.h>"
  #"$<$<COMPILE_LANGUAGE:C>:<stddef.h$<ANGLE-R>>"
  "$<$<COMPILE_LANGUAGE:CXX>:<iostream$<ANGLE-R>>"
  "$<$<COMPILE_LANGUAGE:CXX>:<vector$<ANGLE-R>>"
  "$<$<COMPILE_LANGUAGE:CXX>:<map$<ANGLE-R>>"
)
################################################################################


################################################################################
# Build the executable
#
################################################################################
set(outName              ${PROJECT_NAME}2)   # name of the library
set(srcFiles             "main2.cpp"     )          # all the source files for this library
set(PublicLinkedTargets  ""             )
set(PrivateLinkedTargets ""             )
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

target_precompile_headers( ${outName} REUSE_FROM ${PROJECT_NAME})
################################################################################
