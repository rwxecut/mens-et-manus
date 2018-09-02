cmake_minimum_required(VERSION 3.7)
project(mens_et_manus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

set(SOURCE_FILENAMES
        main.cpp
        Window.cpp
        Shader.cpp
        Texture.cpp
        LuaFile.cpp
        Mod.cpp
        Cam.cpp
        Map.cpp
        Config.cpp
        Logger.cpp
        Tile.cpp
        routines/Splash.cpp
        routines/MainMenu.cpp
        routines/Game.cpp
        lua_binders/nk_lua.cpp
        lua_binders/game_lua.cpp
        lua_binders/modlist_lua.cpp
        auxiliary/primitives.cpp
        auxiliary/util.cpp
        lib/glad.c
        lib/nuklear.cpp
        )

include(prepend)
prepend(SOURCE_FILES ${SOURCE_DIR} ${SOURCE_FILENAMES})

add_executable(mens_et_manus ${SOURCE_FILES})

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS " -static -Wl,-subsystem,console")
endif(WIN32)

set(ENV{LUA_DIR} lib/lua)
set(SDL2_PATH lib/SDL2)
set(SDL2_IMAGE_PATH lib/SDL2_image)

find_package(Lua REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(mens_et_manus PUBLIC
        ${INCLUDE_DIR}
        ${LUA_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        )


target_link_libraries(mens_et_manus
        stdc++fs
        ${LUA_LIBRARIES}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${OPENGL_LIBRARIES}
        )

if (NOT WIN32)
    target_link_libraries(mens_et_manus dl)
endif(NOT WIN32)
