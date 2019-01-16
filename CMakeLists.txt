cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

################### Variables. ####################
# Change if you want modify path or other values. #
###################################################

# Project name
set(PROJECT_NAME DonkeyKong)

# Output Variables
#set(OUTPUT_DEBUG Debug/bin)
#set(OUTPUT_RELEASE Release/bin)

# Library
set(LIBRARY_PATH library)

# SFML Lib
set(SFML_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_PATH}/SFML-2.5.1)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/library/cmake_modules")

############## CMake Project ################
#        The main options of project        #
#############################################

project(${PROJECT_NAME} CXX)

# Definition of Macros
#add_definitions(
#        -D_DEBUG
#        -D_CONSOLE
#        -DUNICODE
#        -D_UNICODE
#)

################# Flags ################
# Defines Flags for Windows and Linux. #
########################################

if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /MD /Od /Zi /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /GL /Od /Oi /Gy /Zi /EHsc")
endif (MSVC)
if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif ()
endif (NOT MSVC)

################ Files ################
#   --   Add files to project.   --   #
#######################################

# Add index CMakeFiles.tkt from /src
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt)

# Add executable to build.
add_executable(${PROJECT_NAME}
        ${SOURCES} src/game/entities/Barrel.cpp src/game/entities/Barrel.h)

# Include directory 
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

################ SFML ##################
#   --   Add library to project.  --   #
########################################

find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif ()