cmake_minimum_required(VERSION 3.0.0)
project(SDL_wasm VERSION 0.1.0)

include(CTest)
enable_testing()

get_filename_component(COMP_FILE_NAME ${CMAKE_C_COMPILER} NAME )
add_executable(SDL_wasm main.cpp)

if("${COMP_FILE_NAME}" MATCHES "emcc")
    message("Compiling with emc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s FETCH=1")
    set(CMAKE_EXECUTABLE_SUFFIX_CXX ".html")
else()

    message("Compiling with gcc")
    find_package(SDL2 REQUIRED)
    target_link_libraries(SDL_wasm SDL2::SDL2)

endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
