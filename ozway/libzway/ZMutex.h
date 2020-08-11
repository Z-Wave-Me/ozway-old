//
//  ZMutex.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 1/7/12.
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

#ifndef zmutex_h
#define zmutex_h

#ifdef _WINDOWS

#define LOCK_INIT(lock) InitializeCriticalSection(lock)
#define LOCK_INIT_EX(lock, attr) LOCK_INIT(lock)
#define LOCK_FREE(lock) DeleteCriticalSection(lock)
#define LOCK_ENTER(lock) EnterCriticalSection(lock)
#define LOCK_EXIT(lock) LeaveCriticalSection(lock)

#else

#define LOCK_INIT(lock) pthread_mutex_init(lock, NULL)
#define LOCK_INIT_EX(lock, attr) pthread_mutex_init(lock, attr)
#define LOCK_FREE(lock) pthread_mutex_destroy(lock)
#define LOCK_ENTER(lock) pthread_mutex_lock(lock)
#define LOCK_EXIT(lock) pthread_mutex_unlock(lock)

#endif

#endif
