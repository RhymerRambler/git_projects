#!/bin/sh
clang -Xclang -load -Xclang ../build/skeleton/libSkeletonPass.so test.cpp
echo $?
