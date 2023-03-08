#!/usr/bin/env bash
sudo apt-get update
sudo apt-get install ninja-build googletest valgrind clang
export CC=$(which clang)
export CXX=$(which clang++)

# install googletest
mkdir /usr/src/googletest/build
cd /usr/src/googletest/build
cmake -G "Ninja" ..
ninja
ninja install
cd -
