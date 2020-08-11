#!/usr/bin/python

import os
import re
from lxml import etree

dir = "."
xsdfile = "z-wave_v2.xsd"

def perror(msg):
	print msg
	exit(1)

try:
	xsd = open(dir + "/" + xsdfile, "r")
except:
	perror("Error opening XSD %s" % xsdfile)

try:
	schema = etree.XMLSchema(etree.parse(xsd))
except:
	perror("Error parsing XSD %s" % xsdfile)

for xmlfile in filter(lambda (x): re.match("^.*\.xml$", x), os.listdir(dir)):
	try:
		xml = open(dir + "/" + xmlfile)
	except:
		perror("Error opening XML %s" % xmlfile)
	try:
		xmldoc = etree.parse(xml)
	except:
		perror("Error parsing XML %s" % xmlfile)
	if schema.validate(xmldoc):
		pass
		#print "%s id valid " % xmlfile
	else:
		print schema.error_log
	xml.close()
