#!/bin/sh

remoteLastChange=`wget 'http://www.pepper1.net/zwavedb/last_change_date.xml' -q -O - | grep "lastChangeDate" | awk -F "[>|<]" '{print $3}'`
localLastChange=`cat last_changed.txt 2>/dev/null`

if [ -z "$remoteLastChange" ]
then
	echo "Can not get last change data from remote side" 1>&2
	exit 1
fi

if [ "$remoteLastChange" != "$localLastChange" ]
then
	echo "Updating ZDD XML database"
	rm *-????-????-????-??-??-??-??-??.xml last_changed.txt ZDDX.indx 2>/dev/null
	wget -q 'http://www.pepper1.net/zwavedb/device/export/device_archive.zip' -O device_archive.zip && sleep 1 && unzip -qq device_archive.zip || err=true # sleep 1 is to wait for write operation - some strange bug!
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
else
	echo "ZDD XML database is already up to date"
fi

