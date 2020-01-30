SET(execName sensorReader)
SET (CMAKE_CXX_STANDARD 14)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(EXECUTABLE_OUTPUT_PATH ".")

SET(SRC_FOLDER src)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries

set(libs
    -lpthread
)

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

FILE(GLOB_RECURSE SRC_FILES
"${SRC_FOLDER}/*.cpp"
)
FILE(GLOB_RECURSE HEADER_FILES
 "${SRC_FOLDER}/*.h"
 )

SET(HEADER_FOLDER include)

add_executable(${execName} ${SRC_FILES} ${HEADER_FILES})
set_property(TARGET ${execName} PROPERTY OUTPUT_NAME "SensorReader")

# Add the required libraries for linking:
TARGET_LINK_LIBRARIES(${execName}
            ${Boost_LIBRARIES}
            ${libs}
 )
