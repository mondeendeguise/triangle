#!/bin/sh

CFLAGS="-Wall -Wextra -pedantic"
LIBS="`pkg-config --libs glew glfw3`"

set -xe

mkdir -p build

clang $CFLAGS -o build/main.o -c src/main.c
clang $CFLAGS -o build/filesystem.o -c src/filesystem.c
clang $CFLAGS -o build/algebra.o -c src/algebra.c

clang -o triangle build/algebra.o build/filesystem.o build/main.o $LIBS
