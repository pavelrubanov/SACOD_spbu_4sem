cmake_minimum_required(VERSION 3.22)

project(ff-lib)

add_library(fflib SHARED
    src/fflib.c
    src/polynom.c
)

add_executable(tests
    tests/main.c
)

target_link_libraries(tests fflib)

target_compile_options(tests PUBLIC -Wall -g)

enable_testing()
add_test(NAME fflib_tests COMMAND tests)

add_custom_target(memcheck COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tests DEPENDS tests)