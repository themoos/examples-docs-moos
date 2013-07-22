#this builds an example program
project(camera_example)
if(COMMAND cmake_policy)
       cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

cmake_minimum_required(VERSION 2.8)

#find MOOS version 10 or later
find_package(MOOS 10)

find_package( OpenCV )

set(EXECNAME video_share)

#what files are needed?
set(SRCS CameraExample.cpp)

#what include directives?
include_directories(  ${MOOS_INCLUDE_DIRS} ${MOOS_DEPEND_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

#make a program!
add_executable(${EXECNAME} ${SRCS} )

#and link thus...
target_link_libraries(${EXECNAME} ${MOOS_LIBRARIES} ${MOOS_DEPEND_LIBRARIES} ${OpenCV_LIBS})