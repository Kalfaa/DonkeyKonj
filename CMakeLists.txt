cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

################### Variables. ####################
# Change if you want modify path or other values. #
###################################################

set(PROJECT_NAME DonkeyKong)
# Output Variables
set(OUTPUT_DEBUG Debug/bin)
set(OUTPUT_RELEASE Release/bin)

#library
set(LIBRARY_PATH library)

############## CMake Project ################
#        The main options of project        #
#############################################

project(${PROJECT_NAME} CXX)

# Define Release by default.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified: Use Release by default.")
endif (NOT CMAKE_BUILD_TYPE)

# Definition of Macros
add_definitions(
        -D_DEBUG
        -D_CONSOLE
        -DUNICODE
        -D_UNICODE
)

############## Artefacts Output #################
# Defines outputs , depending Debug or Release. #
#################################################

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
    set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
else ()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
    set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
endif ()

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
message("${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt")
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt)

# Add executable to build.
message("${HeadersFiles}")
add_executable(${PROJECT_NAME}
            ${HeadersFiles}
            ${CppFiles})

################ SFML ##################
#   --   Add library to project.  --   #
########################################
set(SFML_ROOT ${LIBRARY_PATH}/SFML-2.5.1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/library/cmake_modules")
#message("${CMAKE_MODULE_PATH}")
set(SFML_BUILD_EXAMPLES false)
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
message("${SFML_BUILD_EXAMPLES}")

