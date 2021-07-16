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
    printf "$0: Failed\n"
    exit
fi
mkdir bvmlib-$VERSION    
if [ $? -ne 0 ];
then
    printf "$0: Failed\n"
    exit
fi                                                                                                                                               
cd bvmlib-$VERSION
unzip ../bvmlib-$VERSION.zip
if [ $? -ne 0 ];
then
    printf "$0: Failed\n"
    cd ..
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi
cd ..
BVMLIB_BACKUP=""
if [ -d /usr/local/include/bvmlib ];
then
    printf "$0: Overwriting existing bvmlib\n"
    cp -r /usr/local/include/bvmlib ./bvmlib-backup
    rm -r /usr/local/include/bvmlib
    BVMLIB_BACKUP="./bvmlib-backup"
    printf "$0: Adding bvmlib backup\n"
    if [ $? -ne 0 ];
    then
        printf "$0: Failed\n" 
        rm -r bvmlib-$VERSION
        rm bvmlib-$VERSION.zip
	cp -r ./bvmlib-backup /usr/local/include/bvmlib
	rm -r ./bvmlib-backup
	printf "$0: Restored existing bvmlib\n"
        exit
    fi
fi                                
function rebackup() {
	if [ -d /usr/local/include/bvmlib ];
	then
		rm -r /usr/local/include/bvmlib
	fi
	if [ "$BVMLIB_BACKUP" != "" ];
	then
		printf "$0: Restored existing bvmlib\n"
		cp -r "$BVMLIB_BACKUP" /usr/local/include/bvmlib
		rm -r "$BVMLIB_BACKUP"
	fi
}
cp -r bvmlib-$VERSION /usr/local/include/bvmlib
if [ $? -ne 0 ];
then
    printf "$0: Failed\n" 
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    rebackup
    exit
fi       
touch /usr/local/include/bvmlib/version
if [ $? -ne 0 ];
then
    printf "$0: Failed\n" 
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    rebackup
    exit
fi                                                                                                 
printf "$VERSION" > /usr/local/include/bvmlib/version
if [ $? -ne 0 ];
then
    printf "$0: Failed\n"
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    rebackup
    exit
fi
rm -r bvmlib-$VERSION
if [ $? -ne 0 ];
then
    printf "$0: Failed\n"
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi
rm bvmlib-$VERSION.zip
if [ $? -ne 0 ];
then
    printf "$0: Failed\n"
    rm -r bvmlib-$VERSION
    rm bvmlib-$VERSION.zip
    exit
fi
if [ "$BVMLIB_BACKUP" != "" ];
then
	rm -r "$BVMLIB_BACKUP"
fi
printf "$0: bvmlib installed\n"
