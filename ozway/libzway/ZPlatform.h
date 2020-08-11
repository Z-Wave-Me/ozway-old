//
//  ZPlatform.h
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

#ifndef zplatform_h
#define zplatform_h

#if defined(__linux__) && ! defined(_GNU_SOURCE)
#define _GNU_SOURCE
// this involves __USE_UNIX98 and __USE_GNU
// used for pthread_setname_np, vasprintf, PTHREAD_MUTEX_RECURSIVE and PTHREAD_MUTEX_RECURSIVE_NP
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#ifdef _WINDOWS
	// disable unknown pragma warnings
	#pragma warning(disable: 4068)
    #define TODO(x) __pragma(message("TODO: " #x))
#else
    #ifdef __GNUC__
        #pragma GCC diagnostic ignored "-Wunknown-pragmas"
    #endif
    #define DO_PRAGMA(x) _Pragma (#x)
    #define TODO(x) DO_PRAGMA(message("TODO: " #x))
#endif
          
#ifdef _WINDOWS
    #define ZWINLINE __inline
    #ifdef __cplusplus
        #define ZWEXPORT_PRIVATE extern "C"
        #if defined(ZWAY_STATIC)
            #define ZWEXPORT extern "C"
        #elif defined(ZWAY_EXPORTS)
            #define ZWEXPORT extern "C" __declspec(dllexport)
        #else
            #define ZWEXPORT extern "C" __declspec(dllimport)
        #endif
    #else
        #define ZWEXPORT_PRIVATE extern
        #if defined(ZWAY_STATIC)
            #define ZWEXPORT
        #elif defined(ZWAY_EXPORTS)
            #define ZWEXPORT __declspec(dllexport)
        #else
            #define ZWEXPORT __declspec(dllimport)
        #endif
    #endif
#else
    #define ZWINLINE inline
    #ifdef __cplusplus
        #define ZWEXPORT_PRIVATE extern "C" __attribute((visibility("default")))
        #define ZWEXPORT extern "C" __attribute((visibility("default")))
    #else
        #define ZWEXPORT_PRIVATE __attribute((visibility("default")))
        #define ZWEXPORT __attribute((visibility("default")))
    #endif
#endif

// wrapper for unused variables
#ifdef __GNUC__
#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#ifdef DEBUG
    #define RELEASE_UNUSED(x) x
#else
    #define RELEASE_UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#endif
#else
#define UNUSED(x) UNUSED_ ## x
#ifdef DEBUG
    #define RELEASE_UNUSED(x) x
#else
    #define RELEASE_UNUSED(x) UNUSED_ ## x
#endif
#endif

#define UNUSE(x) (void)(x)

// optional __printflike() specifier (unavailable on some platforms)
#ifndef __printflike
	#ifdef __GNUC__
		#define __printflike(fmtarg, firstvararg) __attribute__((format(printf, fmtarg, firstvararg)))
	#else
		#define __printflike(fmtarg, firstvararg) 
	#endif

	#if _WINDOWS && _MSC_VER >= 1400
		#include <sal.h>
		#if _MSC_VER > 1400
			#define PRINTF_FORMAT_STRING _Printf_format_string_
		#else
			#define PRINTF_FORMAT_STRING __format_string
		#endif
	#else
		#define PRINTF_FORMAT_STRING 
	#endif

#else
	// __printflike defined, no need for other checks
	#define PRINTF_FORMAT_STRING
#endif

#ifdef _WINDOWS

#include <WinSock2.h>
#include <Windows.h>
#include <shlwapi.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <time.h>
#include <tchar.h>

// suppress warnings about deprecated POSIX function names
#pragma warning(disable: 4996)

// suppress warnings about non-dll interface as base class
#pragma warning(disable: 4275)

typedef BYTE ZWBYTE;
typedef unsigned char ZWBOOL;

typedef TCHAR ZWCHAR;
typedef LPTSTR ZWSTR;
typedef LPCTSTR ZWCSTR;

typedef HANDLE ZWHANDLE;

typedef DWORD speed_t;
typedef unsigned short mode_t;

#define copy_str(s) _tcsdup(s)
#define compare_str(s1, s2) _tcscmp(s1, s2)
#define compare_str_ci(s1, s2) _tcsicmp(s1, s2)
#define str_length(s) _tcslen(s)
#define strcasecmp(s1, s2) _stricmp(s1, s2)
#define strncasecmp(s1, s2, maxCount) _strnicmp(s1, s2, maxCount)


#define ZSTR(s) TEXT(s)

typedef HANDLE ZWTHREAD;
typedef CRITICAL_SECTION ZWMUTEX;
typedef DWORD ZWMUTEXATTR;

#define current_thread() GetCurrentThread()

// implementation of UNIX-only functions:

ZWEXPORT_PRIVATE int asprintf(char **buffer, PRINTF_FORMAT_STRING const char *format, ...);
ZWEXPORT_PRIVATE int vasprintf(char **buffer, const char *format, va_list args);
#define snprintf(buffer, size, format, ...) _snprintf(buffer, size, format, __VA_ARGS__)

ZWEXPORT_PRIVATE void flockfile(FILE *filehandle);
ZWEXPORT_PRIVATE void funlockfile(FILE *filehandle);

#define sleep(sec) Sleep((sec) * 1000)
#define sleep_ms(ms) Sleep(ms)

struct timezone 
{
	int tz_minuteswest; /* minutes W of Greenwich */
	int tz_dsttime;     /* type of dst correction */
};

ZWEXPORT_PRIVATE int gettimeofday(struct timeval *tv, struct timezone *tz);

#define O_NOCTTY 0

#else

#if defined(__linux__) && (defined(__i386__) || defined(__x86_64__))
#define __sd_linux_use_directIO__ 1
#include <sys/io.h>
#endif

#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <termios.h>
#include <memory.h>

#define SOCKET_ERROR -1
#define closesocket(x) close(x)
#define _sleep(x) usleep((x) * 1000)

#ifndef O_BINARY
#define O_BINARY 0
#endif

typedef unsigned char ZWBYTE;
typedef unsigned char ZWBOOL;

typedef char ZWCHAR;
typedef char* ZWSTR;
typedef const char* ZWCSTR;

typedef int ZWHANDLE;
typedef int SOCKET;

#define copy_str(s) strdup(s)
#define compare_str(s1, s2) strcmp(s1, s2)
#define compare_str_ci(s1, s2) stricmp(s1, s2)
#define str_length(s) strlen(s)

#define ZSTR(s) s

typedef pthread_t ZWTHREAD;
typedef pthread_mutex_t ZWMUTEX;
typedef pthread_mutexattr_t ZWMUTEXATTR;

#define current_thread() pthread_self()

#define TRUE 1
#define FALSE 0

#define sleep_ms(ms) usleep((ms) * 1000)

#define MAX_PATH FILENAME_MAX

#endif

#ifdef __cplusplus
extern "C" {
#endif

ZWEXPORT_PRIVATE ZWSTR sys_last_err_string();

ZWEXPORT_PRIVATE void get_local_time(struct tm *hosttime, int *msec);
    
ZWEXPORT_PRIVATE uint64_t get_local_time_ms();

ZWEXPORT_PRIVATE int remove_recursive(const char *dirname);

ZWEXPORT_PRIVATE void set_thread_name(const char *name);

#ifdef __cplusplus
}
#endif

#endif
