cmake_minimum_required(VERSION 3.27)
project(MunchLib)

set(CMAKE_CXX_STANDARD 23)

add_executable(Main.MunchLib main.cpp
        munchlib/ccm/src/ccm.cpp
        munchlib/ccm/src/ccm.h
        munchlib/ccm/src/embed.cpp
        munchlib/ccm/src/embed.h
        munchlib/fruchterman/src/fruchterman.h
        munchlib/fruchterman/src/fruchterman.cpp
        munchlib/fruchterman/src/tests.h
        munchlib/fruchterman/src/tests.cpp
        munchlib/ccm/src/tests.h
        munchlib/ccm/src/tests.cpp
        munchlib/ccm/src/knn.cpp
        munchlib/ccm/src/knn.h
        munchlib/ccm/src/utils.cpp
        munchlib/ccm/src/utils.h
        munchlib/ccm/src/interface.cpp
        munchlib/ccm/src/interface.h
        munchlib/ccm/src/interface.cpp)
add_library(munchlib
        munchlib/ccm/src/ccm.cpp
        munchlib/ccm/src/ccm.h
        munchlib/ccm/src/embed.cpp
        munchlib/ccm/src/embed.h
        munchlib/fruchterman/src/fruchterman.h
        munchlib/fruchterman/src/fruchterman.cpp
        munchlib/fruchterman/src/tests.h
        munchlib/fruchterman/src/tests.cpp
        munchlib/ccm/src/tests.h
        munchlib/ccm/src/tests.cpp
        munchlib/ccm/src/knn.cpp
        munchlib/ccm/src/knn.h
        munchlib/ccm/src/utils.cpp
        munchlib/ccm/src/utils.h
        munchlib/ccm/src/interface.cpp
        munchlib/ccm/src/interface.h
        munchlib/ccm/src/interface.cpp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -mno-omit-leaf-frame-pointer")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -mno-omit-leaf-frame-pointer")