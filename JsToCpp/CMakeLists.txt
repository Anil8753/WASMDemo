cmake_minimum_required(VERSION 1.10)

# set the project name
project(JsToCpp)

# emsripten flags  
set(CMAKE_CXX_FLAGS "-std=c++17 -O2 -Wall -Werror -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=5 -s PROXY_TO_PTHREAD=1 -s TOTAL_MEMORY=1073741824 --bind")

# add the executable
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/*.js ${PROJECT_SOURCE_DIR}/web/)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/*.wasm ${PROJECT_SOURCE_DIR}/web/)