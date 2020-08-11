//
//  ZUTF8.h
//  Part of Z-Way.C library
//
//  Created by Poltorak Serguei on 9/23/16.
//
//  Copyright (c) 2016 Z-Wave.Me
//  All rights reserved
//  info@z-wave.me
//
//  This source file is subject to the terms and conditions of the
//  Z-Wave.Me Software License Agreement which restricts the manner
//  in which it may be used.
//

#ifndef zway_utf8_h
#define zway_utf8_h

ZWEXPORT ZWBOOL zutf8_validate(ZWCSTR s);
ZWEXPORT void zutf8_remove_ctrl_chars(ZWCSTR s);

#endif
