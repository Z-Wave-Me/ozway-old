#!/bin/sh

rm *-????-????-????-??-??-??-??-??.xml last_changed.txt ZDDX.indx 2>/dev/null

[ -z "$SKIP_ZME_ZDDX" ] && (
echo "Updating ZDD XML database (source Z-Wave.Me)"
wget -q 'https://service.z-wave.me/ZDDX/device_archive.zip' -O device_archive.zip && sleep 1 && unzip -qq device_archive.zip || err=true # sleep 1 is to wait for write operation - some strange bug!
if [ -z $err ]
then
	rm device_archive.zip
	echo "Done"
else
	echo "Some error happened during ZDD XML database download"
	exit 2
fi
)

echo "Updating ZDD XML database (source Z-Wave Alliance)"
wget -q 'https://support.zwave.eu/zddx.zip' -O device_archive.zip && sleep 1 && unzip -qq device_archive.zip || err=true # sleep 1 is to wait for write operation - some strange bug!
if [ -z $err ]
then
	rm device_archive.zip
	echo "Done"
else
	echo "Some error happened during ZDD XML database download"
	exit 2
fi

python ./MakeIndex.py
if [ $? != 0 ];
then
	echo "Don't forget to run MakeIndex.py manually"
else
	echo "Index created"
fi

