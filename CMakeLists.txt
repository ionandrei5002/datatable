cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(datatable)

include_directories("/usr/include/gtest")

set(HEADERS
    types.h
    viewers/bytebuffer.h
    viewers/value.h
    column.h
    schema.h
    table.h
    reader.h
    writer.h
    values/value.h
    values/bytebuffer.h
    builders.h
    comparators/comparator.h
    iterators/iterator.h

    tests/viewertest.h
    tests/comparatortest.h
    tests/columntest.h
)
set(SOURCES ${HEADERS}
    main.cpp
    viewers/bytebuffer.cpp
    viewers/value.cpp
    column.cpp
    values/bytebuffer.cpp
    values/value.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} pthread gtest gtest_main)

target_compile_options(${PROJECT_NAME}
  PRIVATE
#    -fstack-protector-all
#    -flto
    -march=native
    -std=c++17
#    -O
    -O3
#    -g3
#    -g
    -m64
    -Werror
    -Wno-unused-parameter
    -Wfatal-errors
    -pedantic-errors
    -Wall
    -Wno-missing-braces
    -Wcast-align
    -Wcast-qual
    -Wctor-dtor-privacy
    -Wextra
    -Wformat=2
    -Wmissing-declarations
    -Wno-long-long
    -Wnon-virtual-dtor
    -Woverlength-strings
    -Woverloaded-virtual
    -Wredundant-decls
    -Wreorder
    -Wswitch-default
    -Wunused-variable
    -Wwrite-strings
    -Wno-variadic-macros
    -Wno-unused-local-typedef
    -Wno-language-extension-token
    -fstrict-aliasing
    -Wconversion
    -Wfloat-equal
    -Wold-style-cast
    -Wunreachable-code
    -Wshadow
    -Wpointer-arith
    -Wcast-align
    -Wformat-nonliteral
    -Winit-self
    -floop-parallelize-all
    -ftree-parallelize-loops=4
)
