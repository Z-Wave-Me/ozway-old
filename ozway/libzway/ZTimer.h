//
//  ZTimer.h
//  Part of Z-Way.C library
//
//  Created by Poltorak Serguei on 5/8/17.
//  Based on Z-Way source code written by Christian Paetz and Poltorak Serguei
//
//  Copyright (c) 2017 Z-Wave.Me
//  All rights reserved
//  info@z-wave.me
//
//  This source file is subject to the terms and conditions of the
//  Z-Wave.Me Software License Agreement which restricts the manner
//  in which it may be used.
//

#ifndef zway_timer_h
#define zway_timer_h

typedef void (*ZTimerCallback)(void * arg);

ZWEXPORT ZWError zway_timer_add(ZWay zway, float timeout, ZTimer * timer_p, ZTimerCallback callback, void * arg);
ZWEXPORT ZWError zway_timer_remove(ZWay zway, ZTimer timer);

#endif
