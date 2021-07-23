#!/bin/bash
CC="gcc"
CFILES="main.c"
OUT="../../bin/bvm-linux-test"
CFLAGS="-lbvm -Wall -O2" # -lbvm-static for the static library

function build() {
    "$CC"  $CFLAGS -o "$OUT" $CFILES
}

build