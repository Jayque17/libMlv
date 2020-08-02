#!/bin/bash

mkdir -p build
pushd build
rm -rf ./*
mkdir objs
pushd objs
gcc -I ../../include/ -c ../../src/*.c
popd
mkdir lib
pushd lib
ar -q libMlv.a ../objs/*.o
popd
mkdir libMlv-1.1-build
cp -r ../include lib ../README.md libMlv-1.1-build
tar cvf libMlv-1.1-build.tar libMlv-1.1-build
rm -rf libMlv-1.1-build
popd