#!/bin/bash
if [ $# -lt 1 ];
then
    printf "$0: Version Required\n"
    exit
fi
VERSION="$1"
curl -L https://github.com/GalaxianMonster/bvm/releases/download/$VERSION/bvmlib-$VERSION.zip -o bvmlib-$VERSION.zip
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $?
    exit
fi
mkdir bvmlib-$VERSION    
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $?
    exit
fi                                                                                                                                               
cd bvmlib-$VERSION
unzip ../bvmlib-$VERSION.zip
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $?
    cd ..
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi
cd ..
if [ -d /usr/local/include/bvmlib ];
then
    printf "$0: Overwriting existing bvmlib\n"
    rm -r /usr/local/include/bvmlib
    if [ $? -ne 0 ];
    then
        printf "$0: Failed with exit code %d\n" $? 
        rm -r bvmlib-$VERSION
        rm bvmlib-$VERSION.zip
        exit
    fi
fi                                                                                             
cp -r bvmlib-$VERSION /usr/local/include/bvmlib
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $? 
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi       
touch /usr/local/include/bvmlib/version
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $? 
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi                                                                                                 
printf "$VERSION" > /usr/local/include/bvmlib/version
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $? 
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi
rm -r bvmlib-$VERSION
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $? 
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi
rm bvmlib-$VERSION.zip
if [ $? -ne 0 ];
then
    printf "$0: Failed with exit code %d\n" $? 
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi
printf "$0: bvmlib installed\n"