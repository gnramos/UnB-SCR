#!/bin/bash
#
# @author Guilherme N. Ramos (gnramos@unb.br)
#
# Download and build TORCS/SCR files. Worked on a fresh installation of Ubuntu 14.04.

if [ ! `id -u` = 0 ] ; then
	echo "Need root privileges to do this."
	exit 1
fi

if type torcs >/dev/null; then
	echo "TORCS already installed, won't do anything else."
	exit 0
fi

echo "Check the dependencies..."
# In 2014/10/20, according to http://torcs.sourceforge.net/index.php?name=Sections&op=viewarticle&artid=3#linux-src-all
apt-get install g++ mesa-common-dev freeglut3-dev libplib-dev libalut-dev libvorbis-dev libxi-dev libxmu-dev libxrender-dev libxrandr-dev zlib1g-dev libpng12-dev libxxf86vm-dev -y --force-yes

if [ ! -e torcs_latest.tar.bz2 ] ; then
	echo "Downloading TORCS (into torcs_latest.tar.bz2)..."
	wget http://sourceforge.net/projects/torcs/files/latest/download?source=directory -O torcs_latest.tar.bz2
fi
tar xfj torcs* 
#Usually a big file, better leave it in case something goes wrong
#rm torcs_latest.tar.bz2
cd torcs-*
TORCS_BASE=$(pwd)

if [ -d "scr-patch" ]; then
	if [ ! -e scr-linux-patch.tgz ] ; then
		echo "Downloading SCR (into scr-linux-patch.tgz)..."
		wget http://sourceforge.net/projects/cig/files/SCR%20Championship/Server%20Linux/2.1/scr-linux-patch.tgz/download -O scr-linux-patch.tgz
	fi

	tar xzf scr-linux-patch.tgz
	#rm scr-linux-patch.tgz

	echo "Applying SCR patch..."
	cd scr-patch
	sh do_patch.sh
	cd ..
fi

echo "Installing TORCS..."
./configure
make
sudo make install
sudo make datainstall

export TORCS_BASE=$TORCS_BASE/export
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$TORCS_BASE/lib

if [ -e ../torcs_latest.tar.bz2 ] ; then
	echo "You may want to delete the torcs_latest.tar.bz2 file."
fi
if [ -e torcs_latest.tar.bz2 ] ; then
	scr-linux-patch.tgz
	echo "You may want to delete the scr-linux-patch.tgz file."
fi

cd ..