cmake_minimum_required(VERSION 3.16)
project(Database)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES command/Create.cpp command/Delete.cpp
        command/Drop.cpp
        command/Insert.cpp
        command/Parser.cpp
        command/Select.cpp
        command/Update.cpp
        types/String.cpp
        types/structures.cpp
        FileManager.cpp
        DB.cpp
        ArrayHelper.cpp
        main.cpp)

add_executable(Database ${SOURCES})

file(GLOB TEST_SOURCES
        types/String.cpp
        types/structures.cpp
        command/Parser.cpp
        ArrayHelper.cpp
        test.cpp)
add_executable(Test ${TEST_SOURCES})