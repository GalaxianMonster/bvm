#!/bin/bash
if [ -d /usr/include/bvmlib ];
then
    rm -r /usr/include/bvmlib
fi
cp -r include /usr/include/bvmlib
cd source
if [ ! -e libbvm.a ];
then
	python3 build.py
elif [ ! -e libbvm.so ];
then
	python3 build.py
fi
if [ -e /usr/lib/libbvm-static.a ];
then
    rm /usr/lib/libbvm-static.a
fi
if [ -e /usr/lib/libbvm-static.a ];
then
    rm /usr/lib/libbvm.so
fi
mv libbvm.a /usr/lib/libbvm-static.a
mv libbvm.so /usr/lib/libbvm.so
cd ..
