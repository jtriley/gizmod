#!/bin/bash

PACKAGE="gizmod"

if [ "$1" = "" ] ; then
	echo "Specify a Version"
	exit
fi

echo "Copying to ../$PACKAGE-$1"
cp -r . ../$PACKAGE-$1
cd ../$PACKAGE-$1
echo "Running Autogen"
pwd
sleep 3
./autogen.sh
echo "Configuring"
grc ./configure --with-boost
echo "Cleaning"
make distclean
echo "removing non-dist files"
rm -rf *.kdev* autom4te.cache config.h.in~ documentation debug dependencies optimized valgrind HOWTO *.tag autogen.sh package.sh
for remove in `find . -name \*\.svn` ; do
	rm -rf $remove
done
for remove in `find . -name \*\.pyc` ; do
	rm -rf $remove
done
echo "Packaging"
cd ..
tar jcfh $PACKAGE-$1.tar.bz2 $PACKAGE-$1/*
echo "Done"
