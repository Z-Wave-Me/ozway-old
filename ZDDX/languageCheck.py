#!/usr/bin/python

languages = ("en", "de", "ru")

import os
import re
import xml.dom.minidom

dir = "."

def perror(msg):
	print msg
	exit(1)

def CheckTree(x, path = "/"):
	ret = []
	if not hasattr(x, 'childNodes'):
		return
	if len(filter(lambda y: y.nodeName == "lang", x.childNodes)) == 0:
		for n in x.childNodes:
			ret.extend(CheckTree(n, "%s/%s" % (path, n.nodeName)))
	else:
		languagesChecked = dict((_lang, False) for _lang in languages) # init array
		for n in x.childNodes:
			if n.nodeName == "lang" and len(n.childNodes) > 0 and n.childNodes[0].data.strip() != "":
				lang = n._attrs['xml:lang'].value
				languagesChecked[lang] = True
		for __lang in languagesChecked:
			if not languagesChecked[__lang]:
				ret.append("%s/%s (%s)" % (path, x.nodeName, __lang))
	return ret

for xmlfile in filter(lambda (x): re.match("^.*\.xml$", x), os.listdir(dir)):
	try:
		xmlf = xml.dom.minidom.parse(dir + "/" + xmlfile)
	except:
		perror("Error opening XML %s" % xmlfile)

	ret = CheckTree(xmlf.childNodes[0])
	ret = map(lambda x: "%s %s" % (xmlfile, x), ret)
	print '\n'.join(ret)
