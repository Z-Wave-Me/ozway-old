//
//  ZDataList.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 1/29/12.
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

#ifndef zdata_list_h
#define zdata_list_h

#include "ZDataDefs.h"
#include "ZData.h"

struct _ZDataListEntry
{
    ZDataHolder data;
    ZDataListEntry next;
};

struct _ZDataList
{
    ZDataListEntry first;
    ZDataListEntry last;
    size_t count;
};

ZDataList _zdata_list_create();
void _zdata_list_free(ZDataList list);
void _zdata_list_append(ZDataList list, ZDataHolder data);
void _zdata_list_remove(ZDataList list, ZDataHolder data);

#endif
