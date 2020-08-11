//
//  ZXmlLookup.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 2/5/12.
//  Based on Z-Way source code written by Christian Paetz and Poltorak Serguei
//
//  Copyright (c) 2012 Z-Wave.Me
//  All rights reserved
//  info@z-wave.me
//
//  This source file is subject to the terms and conditions of the
//  Z-Wave.Me Software License Agreement which restricts the manner
//  in which it may be used.
//

#ifndef zway_xml_lookup_h
#define zway_xml_lookup_h

#include <libxml/xpath.h>
#include "ZPlatform.h"
#include "ZMalloc.h"

// Starting from 2.9.4 of LibXML2 prototype of xmlStrPrintf has changed
#if LIBXML_VERSION >= 20904
#define XML_STR_PRINTF_BAD_CAST (char *)
#else
#define XML_STR_PRINTF_BAD_CAST BAD_CAST
#endif

ZWEXPORT_PRIVATE ZWBOOL _xpath_select_boolean(const xmlDocPtr doc, ZWBOOL default_value, PRINTF_FORMAT_STRING const char *path, ...) __printflike(3, 4);

ZWEXPORT_PRIVATE int _xpath_select_integer(const xmlDocPtr doc, int default_value, PRINTF_FORMAT_STRING const char *path, ...) __printflike(3, 4);

ZWEXPORT_PRIVATE float _xpath_select_float(const xmlDocPtr doc, float default_value, PRINTF_FORMAT_STRING const char *path, ...) __printflike(3, 4);

ZWEXPORT_PRIVATE ZWSTR _xpath_select_string(const xmlDocPtr doc, PRINTF_FORMAT_STRING const char *path, ...) __printflike(2, 3);

ZWEXPORT_PRIVATE ZWSTR _xpath_node_to_string(const xmlNodePtr node);

ZWEXPORT_PRIVATE void _xpath_free_nodes(xmlNodeSetPtr nodes);

ZWEXPORT_PRIVATE xmlNodeSetPtr _xpath_select_nodes(const xmlDocPtr doc, PRINTF_FORMAT_STRING const char *path, ...) __printflike(2, 3);

#endif
