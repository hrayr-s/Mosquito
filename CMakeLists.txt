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

#[[file(GLOB
        command/*.h
        command/*.cpp
        types/*.h
        types/*.cpp
        )]]
#add_library(libcmdcreate command/Create.cpp)
#add_library(libcmddelete command/Delete.cpp)
#add_library(libcmddrop command/Drop.cpp)
#add_library(libcmdinsert command/Insert.cpp)
#add_library(libcmdparser command/Parser.cpp)
#add_library(libcmdselect command/Select.cpp)
#add_library(libcmdupdate command/Update.cpp)
#add_library(libtypes types/String.cpp)

add_executable(Database ${SOURCES})