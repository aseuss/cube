cmake_minimum_required(VERSION 3.2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/external/cmake")

message(STATUS "cmake module path: " ${CMAKE_MODULE_PATH})

set(NAME cube)

project(${NAME})

set(${NAME}_VERSION_MAJOR 0)
set(${NAME}_VERSION_MINOR 0)
set(${NAME}_VERSION_PATCH 1)
set(${NAME}_ENGINE_NAME ${NAME}Engine)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/${NAME}_config.h.in
    ${PROJECT_BINARY_DIR}/${NAME}_config.h
)

# add PROJECT_BINARY_DIR to be able to access the generated header
include_directories(${PROJECT_BINARY_DIR})

include_directories(external)
include_directories(external/glm)
#include_directories(external/assimp)
#add_subdirectory(samples)


find_package(ASSIMP REQUIRED)
find_package(Vulkan REQUIRED)

# somehow there are cases where vulkan is found but Vulkan_FOUND is not
# set approprately hence this 'work around'
if(Vulkan_LIBRARY)
    set(Vulkan_FOUND ON)
endif()

if(NOT Vulkan_FOUND)
    message(FATAL_ERROR "could not find vulkan library")
else(NOT Vulkan_FOUND)
    message(STATUS ${Vulkan_LIBRARY})
endif(NOT Vulkan_FOUND)

# define C++ version to be used when building the project
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSION OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define C version to be used for building the project
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


include_directories(${Vulkan_INCLUDE_DIR})

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(samples)

enable_testing()
add_subdirectory(tests)
