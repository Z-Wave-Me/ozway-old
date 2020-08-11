# This file is part of PyZW.
#
# Copyright (C) 2010 Poltorak Serguei
#
# PyZW is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PyZW is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PyZW.  If not, see <http://www.gnu.org/licenses/>.

import xml.dom.minidom
import csv
import os
import re


def GetSubTagChilds(tagList, tagName):
	return filter(lambda (x): x.nodeName == tagName, tagList)[0].childNodes

def GetSubTagValue(tagList, tagName):
        return GetSubTagChilds(tagList, tagName)[0].nodeValue
                
def GetSubTagAttrValue(tagList, tagName):
	return GetTagAttribute(filter(lambda (x): x.nodeName == tagName, tagList), 'value')

def GetSubTagAttribute(tagList, tagName, attrName):
	return GetTagAttribute(filter(lambda (x): x.nodeName == tagName, tagList), attrName)

def GetTagAttribute(tag, attrName):
	return tag[0].getAttribute(attrName)

def CreateXMLIndex():
	"""
	Writes tab separated and XML files with index of all XMLs in the current directory.
	"""

	zddxIndexCSV = "ZDDX.indx"
	zddxIndexXML = "ZDDX.indxml"
	
	##TODO: check XML using XSD: zddxsd = os.path.abspath("%s%s/z-wave_v2.xsd" % (os.getcwd(), device.ZWaveAPI.devices.ZDDXManagedFolder))
	zddxs = filter(lambda (x): re.match("^.*\.xml$", x), os.listdir("."))

	try:
		index = csv.writer(open(zddxIndexCSV, 'wb'), delimiter='\t')
	except Exception, err:
		print("Error creating index file %s: %s" % (zddxIndex, err))
		return -1
	
	doc = xml.dom.minidom.Document()
	root = doc.createElement("ZDDXIndex")
	doc.appendChild(root)
	
	for zddxf in zddxs:
		try:
			zddx = xml.dom.minidom.parse(zddxf)
			
			rootChilds = zddx.childNodes[0].childNodes

			try:
				deviceDescription = GetSubTagChilds(rootChilds, 'deviceDescription')
			except:
				deviceDescription = None
			
			try:
				brandName = GetSubTagValue(deviceDescription, 'brandName')
			except:
				brandName = "";

			try:
				productName = GetSubTagValue(deviceDescription, 'productName')
			except:
				productName = "";
				
			try:
				deviceImage = GetSubTagAttribute(GetSubTagChilds(rootChilds, 'resourceLinks'), 'deviceImage', 'url')
			except:
				deviceImage = "";

			
			deviceData = GetSubTagChilds(rootChilds, 'deviceData')
			
			# Z-Way relies on this order
			fieldNames = [
				'manufacturerId',
				'productType',
				'productId',
				'basicClass',
				'genericClass',
				'specificClass',
				'appVersion',
				'appSubVersion',
				'protoVersion',
				'protoSubVersion',
				'brandName',
				'productName',
				'deviceImageURL',
				'filePath'
			]
			fields = [
				int(GetSubTagAttrValue(deviceData, 'manufacturerId'), 16),
				int(GetSubTagAttrValue(deviceData, 'productType'), 16),
				int(GetSubTagAttrValue(deviceData, 'productId'), 16),
				int(GetSubTagAttrValue(deviceData, 'basicClass'), 16),
				int(GetSubTagAttrValue(deviceData, 'genericClass'), 16),
				int(GetSubTagAttrValue(deviceData, 'specificClass'), 16),
				int(GetSubTagAttrValue(deviceData, 'appVersion'), 16),
				int(GetSubTagAttrValue(deviceData, 'appSubVersion'), 16),
				int(GetSubTagAttrValue(deviceData, 'protoVersion'), 16),
				int(GetSubTagAttrValue(deviceData, 'protoSubVersion'), 16),
				brandName.encode('utf-8'),
				productName.encode('utf-8'),
				deviceImage.encode('utf-8'),
				zddxf.encode('utf-8'),
			]
			
			# Write CSV
			index.writerow(fields)

			# Add to XML
			node = doc.createElement('DeviceDescription')
			for i in range(len(fieldNames)):
				node.setAttribute(fieldNames[i], "%s" % fields[i])
			root.appendChild(node)

			zddx.unlink() # it can not raise exceptions

		except Exception, err:
			print("Error loading Z-Wave Device Description XML %s: %s" % (zddxf, err))
			continue

	xmlf = open(zddxIndexXML, "w")
	xmlf.write(doc.toprettyxml())
	xmlf.close()

print "Creating index file for ZDDX"
if CreateXMLIndex() == None:
	print "Done"
else:
	print "Failed"
