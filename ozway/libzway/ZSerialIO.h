//
//  ZSerialIO.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 1/9/12.
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

#ifndef zway_serial_io_h
#define zway_serial_io_h

#include "ZPlatform.h"
#include "ZLog.h"

#ifdef _WINDOWS
#define S_ISSOCK(x) FALSE
#endif

ZWEXPORT_PRIVATE ZWBOOL zio_open(ZWLog logger, ZWCSTR name, ZWHANDLE *handle);

ZWEXPORT_PRIVATE void zio_close(ZWLog logger, ZWHANDLE *handle);

ZWEXPORT_PRIVATE mode_t zio_type(ZWHANDLE handle);

ZWEXPORT_PRIVATE void zio_configure(ZWLog logger, ZWHANDLE handle, speed_t baudRate);

ZWEXPORT_PRIVATE int zio_write(ZWLog logger, ZWHANDLE handle, const ZWBYTE *buffer, size_t size);

ZWEXPORT_PRIVATE int zio_read(ZWLog logger, ZWHANDLE handle, ZWBYTE *buffer, size_t size);

#endif
