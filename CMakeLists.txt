cmake_minimum_required(VERSION 3.5)

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

# use FindVulkan module if available
if(NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    message(STATUS "using module to find Vulkan")
    find_package(Vulkan REQUIRED)
else(NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    message(STATUS "using own module to find Vulkan")
    include(${CMAKE_CURRENT_SOURCE_DIR}/external/cmake/FindVulkan.cmake)
    #find_package(Vulkan REQUIRED)
endif(NOT CMAKE_VERSION VERSION_LESS 3.7.0)

#if(NOT Vulkan_FOUND)
#    find_library(Vulkan_LIBRARY NAMES vulkan HINTS "$ENV{VULKAN_SDK}/lib" REQUIRED)
#    if (Vulkan_LIBRARY)
#        set(Vulkan_FOUND ON)
#    endif (Vulkan_LIBRARY)
#endif(NOT Vulkan_FOUND)

find_package(ASSIMP REQUIRED)

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

add_subdirectory(src)
add_subdirectory(samples)

