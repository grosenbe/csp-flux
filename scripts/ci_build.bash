#!/usr/bin/env bash
export CC=$(which clang)
export CXX=$(which clang++)

[ ! -d "build" ] && mkdir build
rm -rf build/*
cd build
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=RELEASE ..
ninja cspflux-test && valgrind test/cspflux-test
