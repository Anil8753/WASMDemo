cmake_minimum_required(VERSION 1.10)

# set the project name
project(DebugDemo)

# emsripten flags  
set(CMAKE_CXX_FLAGS "-std=c++17 -g4 EMCC_DEBUG=1 -Wall -Werror --bind")

# add the executable
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/*.js ${PROJECT_SOURCE_DIR}/web/)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/*.wasm ${PROJECT_SOURCE_DIR}/web/)