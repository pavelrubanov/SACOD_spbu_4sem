cmake_minimum_required(VERSION 3.7)

enable_testing()

project (fflib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(fflib src/fflib.c 
                  src/utils.c)

target_include_directories(fflib PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(fflib_tests tests/main.c)

target_include_directories(fflib_tests PRIVATE ${PROJECT_SOURCE_DIR}/tests)
target_link_libraries(fflib_tests fflib)

add_test(NAME fflib COMMAND fflib_tests)

