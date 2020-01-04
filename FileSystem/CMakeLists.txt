cmake_minimum_required(VERSION 1.10)

# set the project name
project(FileSystemAPI)

# emsripten flags 
#set(EMCC_DEBUG 1)
set(CMAKE_CXX_FLAGS "-O3 -s WASM=1  -std=c++17 --bind -s ASSERTIONS=1 -s FETCH=1 -s FORCE_FILESYSTEM=1")

# add the executable
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/*.js ${PROJECT_SOURCE_DIR}/web/)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/*.wasm ${PROJECT_SOURCE_DIR}/web/)

#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/web/src)

#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/web/src)

#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} 
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build/*.map ${PROJECT_SOURCE_DIR}/web/)