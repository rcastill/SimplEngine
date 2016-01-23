cmake_minimum_required(VERSION 3.3)
project(Project_Strat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBSRC_FILES GraphicsEngine.cc GraphicsEngine.h Color.cc Color.h GraphicObject.cc GraphicObject.h Resource.cc Resource.h Texture.cc Texture.h)
set(SOURCE_FILES main.cc TestObject.cc TestObject.h Game.cc Game.h)
add_library(GfxSdlEngine ${LIBSRC_FILES})
add_executable(Project_Strat ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GfxSdlEngine ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

CONFIGURE_FILE(stick.png stick.png COPYONLY)