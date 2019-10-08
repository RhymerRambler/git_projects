#!/bin/sh
set -e

g++ -g -std=c++11 -c graph.cpp
g++ -g -std=c++11 -c DFS.cpp
g++ -g -std=c++11 -c CC.cpp
g++ -g -std=c++11 -c main.cpp
g++ -g -o test graph.o DFS.o main.o


