#!/bin/sh
export LLVM_DIR=/usr/lib/llvm-10/lib/cmake/llvm/
mkdir build
cd build
cmake ..
make
cd ..
