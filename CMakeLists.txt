cmake_minimum_required(VERSION 3.5)
project (VectorClassTemplate)

#=== FINDING PACKAGES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories( ${GTEST_INCLUDE_DIRS})

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall -std=c++11 -g  " )// others compilation flags for debug: -ggdb -fstandalone-debug -W
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#Include dir
include_directories( include )

###=== Library ===
##
### We want to build a static library.
##add_library(IntRange STATIC "src/graal.cpp")
##
###Set the location for library installation -- i.e., /usr/lib in this case
### not really necessary in this example. Use "make install" to apply
##install(TARGETS IntRange ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)
##

#=== Test target ===

### The file(GLOB...) allows for wildcard additions:
##file(GLOB SOURCES_TEST "test/*.cpp" )

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/main.cpp")

# Define the sources
add_executable(vector ${SOURCES} )

# Link with the google test libraries.
target_link_libraries(vector PRIVATE ${GTEST_LIBRARIES} PRIVATE pthread )
