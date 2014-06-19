cmake_minimum_required(VERSION 2.6)
project(libviewer)

################################
# Compiler setup
################################

add_definitions(-Wall)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_INSTALL_PREFIX}/share/cmake/modules")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

################################
# Third party
################################
find_package(OpenGL)
find_package(GLEW)
find_package(GLM)
find_package(GLFW)

set(THIRDPARTY_INCLUDES
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR})

set(THIRDPARTY_LIBRARIES
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY})

################################
# Locate source
################################
file(GLOB_RECURSE INCLUDES include/*.h)
file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE TEST test/*.cpp)

include_directories(include)
include_directories(${THIRDPARTY_INCLUDES})

################################
# Build targets
################################

add_library(viewer SHARED
    ${SRC}
    ${INCLUDES})

target_link_libraries(viewer
    ${THIRDPARTY_LIBRARIES})

add_executable(viewer-test
    ${TEST})

target_link_libraries(viewer-test viewer)

################################
# Resources
################################
file(GLOB_RECURSE SHADERS test/shaders/*.glsl)
file(GLOB_RECURSE TEXTURES test/textures/*.dds)
add_custom_target(resources ALL DEPENDS ${SHADERS} ${TEXTURES})

include("${CMAKE_INSTALL_PREFIX}/share/cmake/includes/Utils.cmake")
copy_resources(resources "${SHADERS}" shaders)
copy_resources(resources "${TEXTURES}" textures)
