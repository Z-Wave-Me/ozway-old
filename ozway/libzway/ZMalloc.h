//
//  ZMalloc.c
//  Part of Z-Way.C library
//
//  Created by Poltorak Serguei on 10/19/12.
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

#ifndef zway_malloc_h
#define zway_malloc_h

#include <stdio.h>
#include "ZPlatform.h"

#define ZASSERT 1 // we always want to have asserts
//#define DEBUG_MALLOC 1

#if DEBUG_MALLOC

#define zmalloc(size)	_zmalloc(size, __FILE__, __LINE__)
#define zrealloc(ptr, size)	_zrealloc(ptr, size, __FILE__, __LINE__)
#define zfree(ptr)		_zfree(ptr, __FILE__, __LINE__)

ZWEXPORT void *_zmalloc(size_t size, const char *file, int line);
ZWEXPORT void *_zrealloc(void *ptr, size_t size, const char *file, int line);
ZWEXPORT void _zfree(void *ptr, const char *file, int line);

#else

#define zmalloc(size)	malloc(size)
#define zrealloc(ptr, size)	realloc(ptr, size)
#define zfree(ptr)		free(ptr)

#endif // DEBUG_MALLOC

#if ZASSERT

#if DEBUG

void _malloc_log_write(PRINTF_FORMAT_STRING const char *format, ...) __printflike(1, 2);

#ifdef __cplusplus

template <typename T>
static T _zassert(T ptr, const char *op, const char *file, int line)
{
    if (ptr != NULL) return ptr;
    
    fprintf(stderr, "Got NULL from %s at %s:%i\n", op, file, line);
    _malloc_log_write("Got NULL from %s at %s:%i\n", op, file, line);
    
    return NULL;
}

#else

ZWEXPORT_PRIVATE void *_zassert(void *ptr, const char *op, const char *file, int line);

#endif


#define zassert(ptr)    _zassert(ptr, #ptr, __FILE__, __LINE__)

#else

#ifdef __cplusplus

template <typename T>
static T _zassert(T ptr, const char *op)
{
    if (ptr != NULL) return ptr;
    
    fprintf(stderr, "Got NULL from %s\n", op);
    
    return NULL;
}

#else

ZWEXPORT_PRIVATE void *_zassert(void *ptr, const char *op);

#endif

#define zassert(ptr)    _zassert(ptr, #ptr)

#endif // DEBUG

#else

#define zassert(ptr)    ptr

#endif // ZASSERT

#endif


