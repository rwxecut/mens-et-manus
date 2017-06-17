cmake_minimum_required(VERSION 3.7)
project(mens_et_manus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/map.cpp)
add_executable(mens_et_manus ${SOURCE_FILES})

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS " -static -Wl,-subsystem,console")
endif()

set(SDL2_PATH ${CMAKE_SOURCE_DIR}/SDL2)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(mens_et_manus ${SDL2_LIBRARY})