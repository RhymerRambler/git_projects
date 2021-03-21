#!/bin/sh
clang -c loglib.c
clang -c -Xclang -load -Xclang ../build/instrument_with_calls/libInstrumentPass.so test.cpp 
#use -S -emit-llvm to dump llvm IR
#clang -S -emit-llvm -Xclang -load -Xclang ../build/instrument_with_calls/libInstrumentPass.so test.cpp 
clang test.o loglib.o -o test.out
echo $?
