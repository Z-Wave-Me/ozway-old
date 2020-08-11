//
//  ZDataExt.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 1/30/12.
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

#ifndef zdata_ext_h
#define zdata_ext_h

#include "ZPlatform.h"
#include "ZWayLib.h"

#ifdef __cplusplus
extern "C" {
#endif

// Search a Data holder by name in controller Data holder
//
// @param: zway
// Z-Way object instance
//
// @param: path
// Path to search for (dot separated)
// NULL or empty string to get root object
//
ZWEXPORT ZDataHolder zway_find_controller_data(const ZWay zway, const char *path);

// Search a Data holder by name in device Data holder
//
// @param: zway
// Z-Way object instance
//
// @param: device_id
// Node Id
//
// @param: path
// Path to search for (dot separated)
// NULL or empty string to get root object
//
ZWEXPORT ZDataHolder zway_find_device_data(const ZWay zway, ZWBYTE device_id, const char *path);

// Search a Data holder by name in instance Data holder
//
// @param: zway
// Z-Way object instance
//
// @param: device_id
// Node Id
//
// @param: instance_id
// Instance Id
//
// @param: path
// Path to search for (dot separated)
// NULL or empty string to get root object
//
ZWEXPORT ZDataHolder zway_find_device_instance_data(const ZWay zway, ZWBYTE device_id, ZWBYTE instance_id, const char *path);

// Search a Data holder by name in Command Class Data holder
//
// @param: zway
// Z-Way object instance
//
// @param: device_id
// Node Id
//
// @param: instance_id
// Instance Id
//
// @param: cc_id
// Command Class Id
//
// @param: path
// Path to search for (dot separated)
// NULL or empty string to get root object
//
ZWEXPORT ZDataHolder zway_find_device_instance_cc_data(const ZWay zway, ZWBYTE device_id, ZWBYTE instance_id, ZWBYTE cc_id, const char *path);

#ifdef __cplusplus
}
#endif

#endif
