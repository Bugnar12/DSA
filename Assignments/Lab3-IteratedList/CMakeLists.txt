cmake_minimum_required(VERSION 3.24)
project(IteratedList_V2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(IteratedList_V2
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        IteratedList.cpp
        IteratedList.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h)
