# ==============================================
# Project Definition and options
# ==============================================
cmake_minimum_required(VERSION 3.31 FATAL_ERROR)
project(OECS)


option(OECS_STATIC OFF)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Define the link libraries
if (OECS_STATIC)
    add_library(OECS STATIC ${SOURCE_FILES})
    message("Linking to OECS statically")
else()
    add_library(OECS SHARED ${SOURCE_FILES})
    message("Linking to OECS dynamically.")
endif()

# Define the include DIRs
target_include_directories(OECS PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_precompile_headers(OECS PRIVATE "$<$<COMPILE_LANGUAGE:C>:${CMAKE_CURRENT_SOURCE_DIR}/include/OECS/PCH.h>")

# Examples
add_executable(example_entity "${CMAKE_CURRENT_SOURCE_DIR}/examples/entities.c")
target_include_directories(example_entity PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(example_entity PRIVATE OECS)

add_executable(example_query "${CMAKE_CURRENT_SOURCE_DIR}/examples/query.c")
target_include_directories(example_query PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(example_query PRIVATE OECS)

add_executable(example_systems "${CMAKE_CURRENT_SOURCE_DIR}/examples/systems.c")
target_include_directories(example_systems PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(example_systems PRIVATE OECS)
