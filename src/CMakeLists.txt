# This file is an index for sources
# message("${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_CURRENT_LIST_DIR}/game/CMakeLists.txt)

set(MAIN_DIR ${CMAKE_CURRENT_LIST_DIR}/main)
set(TOOLS_DIR ${CMAKE_CURRENT_LIST_DIR}/tools)

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/${REGEX_H_CPP})
file(GLOB MAIN ${MAIN_DIR}/${REGEX_H_CPP})
file(GLOB TOOLS ${TOOLS_DIR}/${REGEX_H_CPP})

set(SOURCES ${SRC} ${MAIN} ${TOOLS} ${GAME_SOURCES})
set(INCLUDE_DIR ${INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR} ${TOOLS_DIR})

foreach(SOURCE ${SOURCES})
    message("SOURCE ${SOURCE}")
endforeach()
foreach(DIR ${INCLUDE_DIR})
    message("DIR ${DIR}")
endforeach()

message("INCLUDE_DIR ${INCLUDE_DIR}")