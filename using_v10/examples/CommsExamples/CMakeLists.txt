set(PROJECTNAME MOOSTutorial)

project(${PROJECTNAME})

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

add_subdirectory(EX10)
add_subdirectory(EX20)
add_subdirectory(EX30)
add_subdirectory(EX40)
add_subdirectory(EX50)
add_subdirectory(EX60)