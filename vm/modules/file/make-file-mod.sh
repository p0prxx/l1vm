#!/bin/sh

clang -Wall -fPIC -g -c file.c -O3 -fomit-frame-pointer -g
clang -shared -Wl,-soname,libl1vmfile.so.1 -o libl1vmfile.so.1.0 file.o
cp libl1vmfile.so.1.0 libl1vmfile.so
