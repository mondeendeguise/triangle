#!/bin/sh

CFLAGS="-Wall -Wextra -pedantic"
LIBS="`pkg-config --libs glew glfw3`"

set -xe

cc $CFLAGS -o triangle src/main.c src/filesystem.c $LIBS
