//
//  ZLogging.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 11/03/14.
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

#ifndef zway_logging_h
#define zway_logging_h

#include "ZLog.h"
#include "ZDefsPublic.h"
#include "ZWayLib.h"

#define zway_log(zway, level, message, ...) zlog_write(zway_get_logger(zway), zway_get_name(zway), (level), (message), ##__VA_ARGS__)

#define zway_dump(zway, level, prefix, length, buffer) zlog_dump(zway_get_logger(zway), zway_get_name(zway), level, prefix, length, buffer)

#define zway_log_error(zway, level, message, err) zlog_error(zway_get_logger(zway), zway_get_name(zway), (level), (message), (err))

#endif
