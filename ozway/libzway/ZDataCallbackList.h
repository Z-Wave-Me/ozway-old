//
//  ZDataCallbackList.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 2/8/12.
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

#ifndef zdata_callback_list_h
#define zdata_callback_list_h

#include "ZDataPrivate.h"

struct _ZDataCallbackListEntry
{
    ZDataChangeCallback callback;
    void *arg;
    ZWBOOL watch_children;
    ZDataCallbackListEntry next;
};

struct _ZDataCallbackList 
{
    ZDataCallbackListEntry first;
    ZDataCallbackListEntry last;
};

ZDataCallbackList _zdata_callback_list_create();

void _zdata_callback_list_free(ZDataCallbackList list);

void _zdata_callback_list_add(ZDataCallbackList list, ZDataChangeCallback callback, ZWBOOL notify_parent, void *arg);

void _zdata_callback_list_remove(ZDataCallbackList list, ZDataChangeCallback callback);

void _zdata_callback_list_add_ex(ZDataCallbackList list, ZDataChangeCallback callback, ZWBOOL notify_parent, void *arg);

void _zdata_callback_list_add_nocheck(ZDataCallbackList list, ZDataChangeCallback callback, ZWBOOL notify_parent, void *arg);

void _zdata_callback_list_remove_ex(ZDataCallbackList list, ZDataChangeCallback callback, void *arg);

#endif
