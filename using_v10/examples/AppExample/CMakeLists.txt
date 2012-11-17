#this builds an example program

set(EXECNAME app_example)

find_package(MOOS 10)

#what files are needed?
SET(SRCS ExampleB.cpp)

include_directories(  ${MOOS_INCLUDE_DIRS} ${MOOS_DEPEND_INCLUDE_DIRS})
add_executable(${EXECNAME} ${SRCS} )
target_link_libraries(${EXECNAME} ${MOOS_LIBRARIES} ${MOOS_DEPEND_LIBRARIES})

