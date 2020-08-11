//
//  ZData.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 1/30/12.
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

#ifndef zdata_h
#define zdata_h

#include "ZPlatform.h"
#include "ZErrors.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Don't forget to use locks when updating and reading data:
// zdata_acquire_lock(zway) and zdata_release_lock(zway) have to wrap ALL dataholder operations.
// Note that dataholder/devices/instance/commandclasses change/add/delete callbacks do already have lock aquired, so it is optional to add locks in callback handlers.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifdef __cplusplus
extern "C" {
#endif

struct _ZDataRootObject;
typedef struct _ZDataRootObject *ZDataRootObject;

#define ZDataRoot(root) (ZDataRootObject)(root)

// Available types of Data
enum _ZWDataType
{
    Empty = 0,
    Boolean = 1,
    Integer = 2,
    Float = 3,
    String = 4,
    Binary = 5,
    ArrayOfInteger = 6,
    ArrayOfFloat = 7,
    ArrayOfString = 8
};

// Use this type to define Data type
typedef enum _ZWDataType ZWDataType;

// Z-Way Data holder
struct _ZDataHolder;
typedef struct _ZDataHolder *ZDataHolder;

// Z-Way Data children iterator
struct _ZDataIterator
{
    ZDataHolder data;
};
typedef struct _ZDataIterator *ZDataIterator;

// Types of Data change events
enum _ZWDataChangeType
{
    // Mutually exclusive flags
    Updated = 0x01,       // Value updated or child created
    Invalidated = 0x02,   // Value invalidated
    Deleted = 0x03,       // Data holder deleted - callback is called last time before being deleted
    ChildCreated = 0x04,  // New direct child node created
    
    // TODO: other notification types
    
    // ORed flags
    PhantomUpdate = 0x40, // Data holder updated with same value (only updateTime changed)
    ChildEvent = 0x80     // Event from child node
};

// Use this type to store Data change event type
//typedef enum _ZWDataChangeType ZWDataChangeType;
typedef int ZWDataChangeType;

// Definition of data change callback function
typedef void (*ZDataChangeCallback)(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);


// Invalidates a value in DataHolder
//
// @param: data
// Data object instance
//
// @param: invalidate_children
// Will invalidate all child Data holders if set to True
//
ZWEXPORT ZWError zdata_invalidate(ZDataHolder data, ZWBOOL invalidate_children);

// Attach callback function for Data holder change event
// Supress add of duplicate address of function callback
//
// @param: data
// Data object instance
//
// @param: callback
// Function to be called on change event
// Call sytax is: callback(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);
//
// @param: watch_children
// Will be trigger on child events too
//
// @param: arg
// Additional arguments passed to callback function
// NB! Important not to reffer here to this or other dataholders or their members by pointers!
//
ZWEXPORT ZWError zdata_add_callback(ZDataHolder data, ZDataChangeCallback callback, ZWBOOL watch_children, void *arg);

// Detach callback function from Data holder change event
// Delete all callbacks with same address of function callback
//
// @param: data
// Data object instance
//
// @param: callback
// Function to be detached from change event
//
ZWEXPORT ZWError zdata_remove_callback(ZDataHolder data, ZDataChangeCallback callback);

// Attach callback function for Data holder change event
// Allows many callbacks with same address of callback function (but supress duplicate callback/arg pair)
//
// @param: data
// Data object instance
//
// @param: callback
// Function to be called on change event
// Call sytax is: callback(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);
//
// @param: watch_children
// Will be trigger on child events too
//
// @param: arg
// Additional arguments passed to callback function
// NB! Important not to reffer here to this or other dataholders or their members by pointers!
//
ZWEXPORT ZWError zdata_add_callback_ex(ZDataHolder data, ZDataChangeCallback callback, ZWBOOL watch_children, void *arg);

// Detach callback function from Data holder change event
// Remove only once callback reffered as functio address and argument pair
//
// @param: data
// Data object instance
//
// @param: callback
// Function to be detached from change event
//
// @param: arg
// Additional arguments passed to callback function
//
ZWEXPORT ZWError zdata_remove_callback_ex(ZDataHolder data, ZDataChangeCallback callback, void *arg);

// Set empty value of Data holder
//
// @param: data
// Data object instance
//
ZWEXPORT ZWError zdata_set_empty(ZDataHolder data);

// Set value of Data holder (boolean, integer, float)
//
// @param: data
// Data object instance
//
// @param: value
// New value
//
ZWEXPORT ZWError zdata_set_boolean(ZDataHolder data, ZWBOOL value);
ZWEXPORT ZWError zdata_set_integer(ZDataHolder data, int value);
ZWEXPORT ZWError zdata_set_float(ZDataHolder data, float value);

// Set string value of Data holder
//
// @param: data
// Data object instance
//
// @param: value
// New value
//
// @param: copy
// Copy from user buffer to internal memory if True
//
ZWEXPORT ZWError zdata_set_string(ZDataHolder data, ZWCSTR value, ZWBOOL copy);

// Set string value of Data holder using ptrintf format
// Parsed value is copied to internal memory
//
// @param: data
// Data object instance
//
// @param: format
// Format string in printf style
//
// @param: ...
// Additional parameters parsed in printf style using format string
//
ZWEXPORT ZWError zdata_set_string_fmt(ZDataHolder data, PRINTF_FORMAT_STRING ZWCSTR format, ...) __printflike(2, 3);

// Set array value of Data holder (integer or float)
// Array value is copied to internal memory
//
// @param: data
// Data object instance
//
// @param: value
// New array value
//
// @param: count
// Size of the array
//
ZWEXPORT ZWError zdata_set_integer_array(ZDataHolder data, int *value, size_t count);
ZWEXPORT ZWError zdata_set_float_array(ZDataHolder data, float *value, size_t count);

// Set string array value of Data holder
//
// @param: data
// Data object instance
//
// @param: value
// New array value
//
// @param: length
// Size of the array
//
// @param: copy
// Copy from user buffer to internal memory if True
//
ZWEXPORT ZWError zdata_set_binary(ZDataHolder data, const ZWBYTE *value, size_t length, ZWBOOL copy);

// Set binary value of Data holder
//
// @param: data
// Data object instance
//
// @param: value
// New value
//
// @param: count
// Size (in bytes) of the value
//
// @param: copy
// Copy from user buffer to internal memory if True
//
ZWEXPORT ZWError zdata_set_string_array(ZDataHolder data, ZWCSTR *value, size_t count, ZWBOOL copy);


// Get type of Data holder value
//
// @param: data
// Data object instance
//
// @param: type
// Returned type
//
ZWEXPORT ZWError zdata_get_type(const ZDataHolder data, ZWDataType *type);


// Get Data holder value
//
// @param: data
// Data object instance
//
// @param: value
// Returned value
//
ZWEXPORT ZWError zdata_get_boolean(const ZDataHolder data, ZWBOOL *value);
ZWEXPORT ZWError zdata_get_integer(const ZDataHolder data, int *value);
ZWEXPORT ZWError zdata_get_float(const ZDataHolder data, float *value);
ZWEXPORT ZWError zdata_get_string(const ZDataHolder data, ZWCSTR *value);

// Get Data holder value
//
// @param: data
// Data object instance
//
// @param: value
// Returned value
//
// @param: count
// Size of the returned array
//
ZWEXPORT ZWError zdata_get_integer_array(const ZDataHolder data, const int **value, size_t *count);
ZWEXPORT ZWError zdata_get_float_array(const ZDataHolder data, const float **value, size_t *count);
ZWEXPORT ZWError zdata_get_string_array(const ZDataHolder data, const ZWCSTR **value, size_t *count);

// Get Data holder value
//
// @param: data
// Data object instance
//
// @param: value
// Returned value
//
// @param: length
// Size of the returned value
//
ZWEXPORT ZWError zdata_get_binary(const ZDataHolder data, const ZWBYTE **value, size_t *length);

// Search a Data holder by name starting from a defined Data holder
//
// @param: data
// Root object instance
//
// @param: path
// Path to search for (dot separated)
//
ZWEXPORT ZDataHolder zdata_find(const ZDataHolder data, const char *path);

// Checks if dataholder holds empty value
//
// @param: data
// Data object instance
//
ZWEXPORT ZWBOOL zdata_is_empty(const ZDataHolder data);

// Returns DataHolder path starting from it's root
// Important: Should be freed by caller !!
//
// @param: data
// Data object instance
//
ZWEXPORT char *zdata_get_path(const ZDataHolder data);

// Returns DataHolder local name
// Important: Returns a real value, not a copy. SHOULD NOT be freed !!
//
// @param: data
// Data object instance
//
ZWEXPORT const char *zdata_get_name(const ZDataHolder data);

// Returns DataHolder first child embedded in iterator structure
//
// @param: data
// Data object instance
//
ZWEXPORT ZDataIterator zdata_first_child(const ZDataHolder data);

// Returns DataHolder next child embedded in iterator structure
//
// @param: child
// Previous child Data object instance
//
ZWEXPORT ZDataIterator zdata_next_child(ZDataIterator child);

// Removes child DataHolder from the parent
// Note that child is freed, so it is no longer valid after this call
//
// @param: data
// Data object instance
//
// @param: child
// Immediate child data object instance
//
ZWEXPORT ZWError zdata_remove_child(ZDataHolder data, ZDataHolder child);

// Returns DataHolder update time
// 
// @param data
// Data object instance
//
ZWEXPORT time_t zdata_get_update_time(const ZDataHolder data);

// Returns DataHolder invalidate time
// 
// @param data
// Data object instance
//
ZWEXPORT time_t zdata_get_invalidate_time(const ZDataHolder data);

// Acquires/releases data lock for several sequential operations with DataHolder(s)
//
// @param root
// ZData root object instance
//
ZWEXPORT void zdata_acquire_lock(ZDataRootObject root);
ZWEXPORT void zdata_release_lock(ZDataRootObject root);

#ifdef __cplusplus
}
#endif
    
#endif
