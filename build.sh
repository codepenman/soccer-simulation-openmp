#!/bin/sh

#Run . build.sh "path to boost libraries"
#Example ~$ . build.sh "/usr/local/lib/boost"

make clean
make
if [ ! -z "$LD_LIBRARY_PATH" -a "$LD_LIBRARY_PATH" != " " ]; then
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$1
else
	export LD_LIBRARY_PATH=$1
fi
echo $LD_LIBRARY_PATH
