//
//  ZDefsPublic.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 1/26/12.
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

#ifndef zway_defs_public_h
#define zway_defs_public_h

#include "ZPlatform.h"
#include "ZData.h"
#include "ZMalloc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Broadcast Node Id
#define NODE_BROADCAST 0xFF
// Maximum allowed Node Id
#define NODE_MAX 0xE8

// ZWay defs //

// State of controller
enum _ZWControllerState
{
    Idle = 0,             // Normal operation
    
    AddReady = 1,         // Ready to include device
    AddNodeFound = 2,     // Node found
    AddLearning = 3,      // Assigning NodeId
    AddDone = 4,          // Inclusion done
    
    RemoveReady = 5,      // Ready to exclude device
    RemoveNodeFound = 6,  // Node found
    RemoveLearning = 7,   // Assigning NodeId to zero

    // (historically 8 and 9 are in wrong order - will not change anymore to keep compatibility)
    LearnStarted = 8,     // Inclusion done
    LearnReady = 9,       // Start including in foreign network
    LearnPrepareNWI = 10, // Stopped inclusion to start again in NWI mode
    LearnDiscover = 11,   // Discovery of network after inclusion
    
    // 12,                // unused
    
    ShiftReady = 13,      // Ready to include controller and shift primary role
    ShiftNodeFound = 14,  // Node found
    ShiftLearning = 15,   // Assigning NodeId
    ShiftDone = 16,       // Controller shift done
    
    // 17,                // unused
    
    ReplaceStarted = 18,  // Ready to include a replacement
    ReplaceReady = 19,    // Replace done
    
    Resetting = 20,       // Resetting controller
};

// Use this type to save controller state
typedef int ZWState;

// Z-Way instance holder
struct _ZWay;
typedef struct _ZWay *ZWay;

// Definition of termination callback function
typedef void (*ZTerminationCallback)(const ZWay zway, void* arg);

// ZJob defs //

// Definition of custom callback for Function Classes and Command Classes calls
typedef void (*ZJobCustomCallback)(const ZWay zway, ZWBYTE functionId, void* arg);

// Types of Device change events
enum _ZWDeviceChangeType
{
    DeviceAdded = 0x01,
    DeviceRemoved = 0x02,
    InstanceAdded = 0x04,
    InstanceRemoved = 0x08,
    CommandAdded = 0x10,
    CommandRemoved = 0x20,
    ZDDXSaved = 0x100, // this callback notifies on ZDDX data change (to allow main program to purge buffers to disk/flash). For this event node_id = instance_id = command_id = 0
    EnumerateExisting = 0x200, // this flag makes callback immediately fire for all existing devices/instances/command classes as if they're just added
};

// Use this type to store Device change event type
typedef int ZWDeviceChangeType;

// Definition of device change callback function
typedef void (*ZDeviceCallback)(const ZWay zway, ZWDeviceChangeType type, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE command_id, void *arg);

// ChooseXml enumerator
struct _ZGuessedProduct
{
    int score;
    int manufacturerId;
    int productTypeId;
    int productId;
    char *vendor;
    char *product;
    char *image_url;
    char *product_code;
    char *rffrequency;
    char *file_name;
};
typedef struct _ZGuessedProduct *ZGuessedProduct;

// ZTimer defs
struct _ZTimer;
typedef struct _ZTimer *ZTimer;

// List of NULL terminated registered devices Node Id
typedef ZWBYTE * ZWDevicesList;

// List of NULL terminated registered instances Id for device
typedef ZWBYTE * ZWInstancesList;

// List of NULL terminated registered Command Classes Id for instance of device
typedef ZWBYTE * ZWCommandClassesList;

// All byte and word values are represented by int with -1 as "no value"
typedef struct NodeProvisioningData {
    // TLV ProductType
    int deviceType;
    int installerIconType;

    // TLV ProductID
    int manufacturerId;
    int productTypeId;
    int productId;
    int applicationVersion;

    int maxInclusionRequestInterval;

    ZWBYTE* UUID16;

    ZWCSTR nameDSK;
    ZWCSTR location;

    int smartStartInclusionSetting;
    int advancedJoining;
    int bootstrappingMode;
    int networkStatus;
} NodeProvisioningData;

// RSSI in dBm (signed byte from -128 to 10)
#define RSSI_VALID_LOWEST        -94 // Valid values are in range -94 .. -32
#define RSSI_VALID_HIGHEST       -32
#define RSSI_BELOW_SENSITIVITY   125 // No signal detected. The RSSI is too low to measure precisely
#define RSSI_MAX_POWER_SATURATED 126 // Receiver saturated. RSSI too high to measure precisely
#define RSSI_NOT_AVAILABLE       127 // RSSI measurement not available

// Transport routing scheme state definitions
/* 1 = direct, 2 = ApplicationStaticRoute, 3 = responseRoute/lastworkingRoute, */
/* 4 = Next to LastWorkingRoute(controller), 5 = returnRoute/controllerAutoRoute, 6 = directResort and 7 = explore */
#define ROUTINGSCHEME_IDLE		0
#define ROUTINGSCHEME_DIRECT		1 // direct
#define ROUTINGSCHEME_CACHED_ROUTE_SR	2 // application static route
#define ROUTINGSCHEME_CACHED_ROUTE	3 // response route/last working route
#define ROUTINGSCHEME_CACHED_ROUTE_NLWR	4 // next to last working route
#define ROUTINGSCHEME_ROUTE		5 // return route/controller auto route
#define ROUTINGSCHEME_RESORT_DIRECT	6 // direct resort
#define ROUTINGSCHEME_RESORT_EXPLORE	7 // explore
    
#ifdef __cplusplus
}
#endif
    
#endif

