cmake_minimum_required(VERSION 3.16)
project(Projekt_2_AZO)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        utils
        MST
)

add_executable(Projekt2AZO
        main.cpp
        utils/graph.cpp
        MST/prim.cpp
        MST/kruskal.cpp
        Path/dijkstra.cpp
        Path/dijkstra.h
        Path/bellmanford.cpp
        Path/bellmanford.h
)