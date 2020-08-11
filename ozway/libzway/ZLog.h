//
//  ZLog.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 1/6/12.
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

#ifndef zlog_h
#define zlog_h

#include "ZPlatform.h"
#include "ZErrors.h"

// Available logging levels
enum _ZWLogLevel
{
    Debug = 0,
    Information = 1,
    Warning = 2,
    Error = 3,
    Critical = 4,
    Silent = 5
};

// Use this type to define logging level
typedef int ZWLogLevel;

struct _ZWLog;
typedef struct _ZWLog *ZWLog;

ZWEXPORT ZWLog zlog_create(FILE *file, ZWLogLevel level);

ZWEXPORT ZWLog zlog_create_syslog(ZWLogLevel level);

ZWEXPORT void zlog_close(ZWLog log);

ZWEXPORT void zlog_change(ZWLog log, FILE *file, ZWLogLevel level);

ZWEXPORT void zlog_write(ZWLog log, ZWCSTR source, ZWLogLevel level, PRINTF_FORMAT_STRING ZWCSTR message, ...) __printflike(4, 5);

ZWEXPORT void zlog_dump(ZWLog log, ZWCSTR source, ZWLogLevel level, ZWCSTR prefix, size_t length, const ZWBYTE *buffer);

ZWEXPORT void zlog_error(ZWLog log, ZWCSTR source, ZWLogLevel level, ZWCSTR message, ZWError error);

#endif // zlog_h
