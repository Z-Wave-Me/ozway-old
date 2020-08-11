//
//  ZWayLib.h
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

#ifndef zway_h
#define zway_h

#include "ZErrors.h"
#include "ZLog.h"
#include "ZDefsPublic.h"
#include "FunctionClassesPublic.h"
#include "CommandClassesPublic.h"
#include "ZDataExt.h"

// Allocate and initialize a ZWay object
//
// @param pzway:     
// pointer that gets a ZWay object
// Note! ZWay structure must be filled with zeros first!
//
// @param port:     
// name of port to connect to.
// either serial port (COM1 or /dev/ttyUSB0),
//
// @param config_folder:
// path to config files
// NULL for current folder
// 
// @param translations_folder:
// path to translation files
// NULL for current folder
// 
// @param zddx_folder:
// path to zddx files
// NULL for current folder
//
// @param name
// Instance name to distinguish messages in log
//
// @param logger
// Logger to write messages to
//
ZWEXPORT ZWError zway_init(ZWay *pzway, ZWCSTR port, ZWCSTR config_folder, ZWCSTR translations_folder, ZWCSTR zddx_folder, ZWCSTR name, ZWLog logger);

// Save state, close all handles and deallocate a ZWay object
//
// @param pzway:
// pointer to ZWay object
// set to NULL on return
//
ZWEXPORT void zway_terminate(ZWay *pzway);

// Start worker thread and open port
//
// @param zway:
// ZWay object instance
//
// @param termination_callback:
// function called on termination of Z-Way worker thread (underlying device has gone)
// Syntax is (void) termination_callback(ZWay zway)
// NULL if callback is not needed
// Note, that the callback is called in Z-Way worker thread.
// Jobs are not processed anymore, but Data Holders are still available.
//
// @param arg:
// optional arg passed to termination callback
//
ZWEXPORT ZWError zway_start(ZWay zway, ZTerminationCallback termination_callback, void* arg);

// Stop processing of commands and terminate worker thread
//
// @param zway:
// ZWay object instance
//
ZWEXPORT ZWError zway_stop(ZWay zway);

// Returns logger instance used by zway object
//
// @param zway:
// ZWay object instance
//
ZWEXPORT ZWLog zway_get_logger(ZWay zway);

// Returns instance name for zway object
//
// @param zway:
// ZWay object instance
//
ZWEXPORT ZWCSTR zway_get_name(ZWay zway);

// Discover Home ID, get network topology, version, capabilities etc.
// Function exits only then discovery finished (successfully or unsuccessfully).
//
// @param zway:
// ZWay object instance
//
ZWEXPORT ZWError zway_discover(ZWay zway);

// Check if queue is empty (or has only jobs in state 'Done')
//
// @param zway:
// ZWay object instance
//
ZWEXPORT ZWBOOL zway_is_idle(ZWay zway);

// Check that Z-Way is still running (Z-Way working thread still works).
// termination_callback parameter of zway_start() can be used as alternative to this function.
//
// @param zway:
// ZWay object instance
//
ZWEXPORT ZWBOOL zway_is_running(ZWay zway);

// Send NoOperation to a node and wake up it's queue.
// Used to explicitelly check if mains powered is reachable or the battery device is currently awake and mark it as failed if not reachable (after this it is possible to do RemoveFailed).
//
// @param zway:
// ZWay object instance
//
// @param node_id:
// NodeId
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
// Even on non-delivered packet successCallback is called after IsFailed call
// To check device reachability look on isFailed flag
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_device_send_nop(ZWay zway, ZWBYTE node_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Loads Device Description XML (ZDDX) file for specified device
//
// @param zway:
// ZWay object instance
//
// @param node_id:
// NodeId
//
// @param file_name:
// XML file name
//
ZWEXPORT ZWError zway_device_load_xml(const ZWay zway, ZWBYTE node_id, ZWCSTR file_name);

// Returns a list of ZDDX files with match score for the desired devices.
// (NULL terminated array of ZGuessedProduct structures).
// The list is sorted in descending order.
// Full match is score = 10.
// Currently selected ZDDX record (if any) have 100 added to it's score.
//
// @param zway:
// ZWay object instance
//
// @param node_id:
// NodeId
//
ZWEXPORT ZGuessedProduct *zway_device_guess(const ZWay zway, ZWBYTE node_id);

// Free memory allocated by zway_device_guess function.
//
// @param products
// Pointer to the array returned previously by zway_device_guess
//
ZWEXPORT void zway_device_guess_free(ZGuessedProduct *products);

// Force queue wakeup for a device
// Try to deliver jobs in the queue for the specified device.
// Note that jobs in the queue might be marked again as W (wait for wakeup) after first unsuccessful delivery.
//
// @param zway:
// ZWay object instance
//
// @param node_id:
// NodeId
//
ZWEXPORT void zway_device_awake_queue(const ZWay zway, ZWBYTE node_id);

// Attach callback function from Device change event.
// Duplicate address add of function callback is suppressed (one callback can be binded only once).
//
// @param zway:
// Z-Way object instance
//
// @param mask:
// Mask of which events to watch
//
// @param callback:
// Function to be attached to change event
//
// @param arg:
// Custom argument for callback function
//
ZWEXPORT ZWError zway_device_add_callback(const ZWay zway, ZWDeviceChangeType mask, ZDeviceCallback callback, void *arg);

// Detach callback function from Device change event
// Delete all callbacks with same address of function callback
//
// @param zway:
// Z-Way object instance
//
// @param callback:
// Function to be detached from change event
//
ZWEXPORT ZWError zway_device_remove_callback(const ZWay zway, ZDeviceCallback callback);

// Attach callback function from Device change event
// Allows many callbacks with same address of callback function (but supress duplicate callback/arg pair)
//
// @param zway:
// Z-Way object instance
//
// @param mask:
// Mask of which events to watch
//
// @param callback:
// Function to be attached to change event
//
// @param arg:
// Custom argument for callback function
//
ZWEXPORT ZWError zway_device_add_callback_ex(const ZWay zway, ZWDeviceChangeType mask, ZDeviceCallback callback, void *arg);

// Detach callback function from Device change event
// Remove only once callback referred as function address and argument pair
//
// @param zway:
// Z-Way object instance
//
// @param callback:
// Function to be detached from change event
//
ZWEXPORT ZWError zway_device_remove_callback_ex(const ZWay zway, ZDeviceCallback callback, void *arg);

// Run Command Class Interview.
//
// @param zway:
// Z-Way object instance
//
// @param device_id:
// Node Id
//
// @param instance_id:
// Instance Id
//
// @param cc_id:
// Command Class Id
//
ZWEXPORT ZWError zway_command_interview(const ZWay zway, ZWBYTE device_id, ZWBYTE instance_id, ZWBYTE cc_id);

// Force re-interview of the device.
// Deletes Command Class and Instance structures,
// renders them from scratch based on NIF and mandatory Command Claasses and
// runs interview.
//
// @param zway:
// Z-Way object instance
//
// @param device_id:
// Node Id
//
ZWEXPORT ZWError zway_device_interview_force(const ZWay zway, ZWBYTE device_id);

// Check if device interview is done (all Command Classes interview are done).
//
// @param zway:
// Z-Way object instance
//
// @param device_id:
// Node Id
//
// @param instance_id:
// Instance Id
//
ZWEXPORT ZWBOOL zway_device_is_interview_done(const ZWay zway, ZWBYTE device_id);

// Assigns return route to a device.
// Use this function instead of directly calling Function Class AssignReturnRoute
// since this function also handles controller/slave difference.
//
// @param zway:
// Z-Way object instance
//
// @param device_id:
// Node Id of the device saving the new route
//
// @param node_id:
// Node Id of the device to save the route to
//
ZWEXPORT ZWError zway_device_assign_return_route(const ZWay zway, ZWBYTE device_id, ZWBYTE node_id);

// Deletes ALL return route in device
// Use this function instead of directly calling Function Class DeleteReturnRoute
// since this function also handles controller/slave difference
//
// @param zway:
// Z-Way object instance
//
// @param device_id:
// Node Id of the device cleaning return routes
//
ZWEXPORT ZWError zway_device_delete_return_route(const ZWay zway, ZWBYTE device_id);

// Assigns SUC return route to a device
// Use this function instead of directly calling Function Class AssignSUCReturnRoute
// since this function also handles controller/slave difference
//
// @param zway:
// Z-Way object instance
//
// @param device_id:
// Node Id of the device saving the new route to SUC
//
ZWEXPORT ZWError zway_device_assign_suc_return_route(const ZWay zway, ZWBYTE device_id);

// Deletes SUC return route in device
// Use this function instead of directly calling Function Class DeleteSUCReturnRoute
// since this function also handles controller/slave difference
//
// @param zway:
// Z-Way object instance
//
// @param device_id:
// Node Id of the device cleaning SUC return route
//
ZWEXPORT ZWError zway_device_delete_suc_return_route(const ZWay zway, ZWBYTE device_id);

// Set Static Update Controller (SUC) in the network and inform other devices about the assignment.
// Use this function instead of directly calling Function Class SetSUCNodeId
// since this function handles EnableSUC and SendSUCNodeId/AssignSUCReturnRoute calls.
//
// @param zway:
// Z-Way object instance
//
// @param node_id:
// Node Id to be come the new SUC
//
ZWEXPORT ZWError zway_controller_set_suc_node_id(ZWay zway, ZWBYTE node_id);

// Set SUC ID Server (SIS) in the network and inform other devices about the assignment.
// Use this function instead of directly calling Function Class SetSUCNodeId
// since this function handles EnableSUC/EnableSIS and SendSUCNodeId/AssignSUCReturnRoute calls.
//
// @param zway:
// Z-Way object instance
//
// @param node_id:
// Node Id to be come the new SIS
//
ZWEXPORT ZWError zway_controller_set_sis_node_id(ZWay zway, ZWBYTE node_id);

// Disable SUC/SIS in the network and inform other devices about the assignment.
// Use this function instead of directly calling Function Class SetSUCNodeId
// since this function handles DisableSUC and SendSUCNodeId/DeleteSUCReturnRoute calls.
//
// @param zway:
// Z-Way object instance
//
// @param node_id:
// Node Id to revoke SUC/SIS role from
//
ZWEXPORT ZWError zway_controller_disable_suc_node_id(ZWay zway, ZWBYTE node_id);

// Set new primary controller (also known as Controller Shift)
// Same as Inclusion, but the newly included device will get the role of primary.
// Available only on primary controller.
//
// @param zway:
// Z-Way object instance
//
// @param startStop:
// Start create new primary mode if True, stop if False
//
ZWEXPORT ZWError zway_controller_change(ZWay zway, ZWBOOL startStop);

// Start/stop Inclusion of a new node
// Available on primary and inclusion controllers
//
// @param zway:
// Z-Way object instance
//
// @param startStop:
// Start inclusion mode if True, stop if False
//
ZWEXPORT ZWError zway_controller_add_node_to_network(ZWay zway, ZWBOOL startStop);

// Start/stop exclusion of a node
// Note that this function can be used to exclude a device from previous network before including in ours.
// Available on primary and inclusion controllers
//
// @param: zway
// Z-Way object instance
//
// @param: startStop
// Start exclusion mode if True, stop if False
//
ZWEXPORT ZWError zway_controller_remove_node_from_network(ZWay zway, ZWBOOL startStop);

// Set/stop Learn mode
// Tries first classical inclusion then falls back to NWI automatically.
//
// @param: zway
// Z-Way object instance
//
// @param: startStop
// Start Learn mode if True, stop if False.
//
ZWEXPORT ZWError zway_controller_set_learn_mode(ZWay zway, ZWBOOL startStop);

// Reset the controller
// Note: this function will delete ALL data from the Z-Wave chip and restore it to factory default !
// Sticks based on 4.5x and 6.x SDKs will also generate a new Home Id.
//
// @param: zway
// Z-Way object instance
//
ZWEXPORT ZWError zway_controller_set_default(ZWay zway);

// Saves controller configuration, defaults and other needed files as tgz archive
//
// @param: zway
// Z-Way object instance
//
// @param: data
// Pointer to a variable that will receive an allocated data buffer
// It should be freed by caller when it is no longer needed
//
// @param: length
// Pointer to a variable that will receive data length
//
ZWEXPORT ZWError zway_controller_config_save(ZWay zway, ZWBYTE **data, size_t *length);

// Restores controller configuration, defaults and other needed files from tgz archive
// Note: This function restores homeId, nodeId and information about nodes in network.
// The controller would be PRIMARY after this restore!
// 
// It has a lot of side effects! After this function consider:
// - run routing healing
// - change the SUC if it was not on the restored node
// - inform all nodes about new SUC/SIS
//
// @param: zway
// Z-Way object instance
//
// @param: data
// Data buffer with archive contents
//
// @param: length
// Data length
//
// @param: full
// Perform full restore (including home id and network topology)
//
ZWEXPORT ZWError zway_controller_config_restore(ZWay zway, const ZWBYTE *data, size_t length, ZWBOOL full);

// Adds DSK to DSKList
//
// @param: zway
// Z-Way object instance
//
// @param: dskLength
// DSK length
//
// @param: dsk
// Data buffer with DSK
//
// @param: dataPtr
// Metadata
//
ZWEXPORT ZWError zway_node_provisioning_dsk_add(ZWay zway, ZWBYTE dskLength, const ZWBYTE *dsk, NodeProvisioningData *dataPtr);

// Removes DSK from DSKList
//
// @param: zway
// Z-Way object instance
//
// @param: dskLength
// DSK length
//
// @param: dsk
// Data buffer with DSK
//
ZWEXPORT ZWError zway_node_provisioning_dsk_remove(ZWay zway, ZWBYTE dskLength, const ZWBYTE *dsk);

// Save all Z-Way data to the disc
// This function runs after each step of interview (configurable in Defaults.xml) and
// at Z-Wave library termination
//
// Run this function from time to time to have current data for persistance.
//
// The file is named config/zddx/<homeId>-DevicesData.xml (see config_folder parameter in zway_init) and is read only on Z-Way library startup.
//
// @param zway:
// Z-Way object instance
//
ZWEXPORT ZWError zddx_save_to_xml(const ZWay zway);

// Returns 0 terminated list of registered devices Node Id.
// NULL is returned if incorrect Z-Way object is given.
//
// @param zway:
// Z-Way object instance
//
ZWEXPORT ZWDevicesList zway_devices_list(const ZWay zway);

// Free list of registered devices Node Id previously allocated by zway_devices_list.
//
// @param list:
// List to be freed
//
ZWEXPORT void zway_devices_list_free(ZWDevicesList list);

// Returns 0 terminated list of registered instances Id for specified device.
// Note, that instance 0 is not included in the list (since it is zero terminated), but is ALWAYS present for a device as device->default_instance obejct.
// NULL is returned if incorrect Z-Way object is given or device does not exist.
//
// @param zway:
// Z-Way object instance
//
// @param deviceId:
// Device in question
//
ZWEXPORT ZWInstancesList zway_instances_list(const ZWay zway, ZWBYTE deviceId);

// Free list of registered instances Id for specified device previously allocated by zway_instances_list.
//
// @param list:
// List to be freed
//
ZWEXPORT void zway_instances_list_free(ZWInstancesList list);


// Returns 0 terminated list of registered Command Classes Id for specified instance of device
// NULL is returned if incorrect Z-Way object is given or device does not exist or instance does not exist.
//
// @param zway:
// Z-Way object instance
//
// @param deviceId:
// Device in question
//
// @param instanceId:
// Instance in question
//
ZWEXPORT ZWCommandClassesList zway_command_classes_list(const ZWay zway, ZWBYTE deviceId, ZWBYTE instanceId);

// Free list of registered Command Classes Id for specified instance of device previously allocated by zway_command_classes_list.
//
// @param list:
// List to be freed
//
ZWEXPORT void zway_command_classes_list_free(ZWCommandClassesList list);

// Returns if command class both exists for specified instance of device, and is rendered as supported
//
// @param zway:
// Z-Way object instance
//
// @param node_id:
// Device in question
//
// @param node_id:
// Instance in question
//
// @param command_id:
// Command class in question
//
ZWEXPORT ZWBOOL zway_command_is_supported(const ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE command_id);


// Prints into provided stream debug information about queue content.
// Queue includes pending jobs, processing jobs as well as done jobs for some period to help analyse outgoing queue.
// The output contains one job per line with few fields describing the job:
//  Send count
//  Status
//  Wait for Serial API ACK
//  Wait for Serial API Response
//  Wait for Serial API Callback
//  Timeout in ms
//  Destination node ID (or 0 if not to node)
//  Frame type
//  Serial API Function ID
//  Payload
//  Serial API Callback ID
//  Job description
// The format is %hhi %c %c %c %c %3.2f %3hhi ( %02hhX %02hhX %s %02hhX) %s\n
// Status:
//  D - done
//  W - waiting for wakeup of the device
//  S - waiting for security session
//  (space) - job to be processed
// Wait for Serial API ...:
//  (space) - no need to wait for message of that type
//  - - wait for message
//  + - message received
//
// @param zway:
// Z-Way object instance
//
// @param node_id:
// Device in question
//
// @param node_id:
// Instance in question
//
// @param command_id:
// Command class in question
//
ZWEXPORT void zway_queue_inspect(const ZWay zway, FILE * stream);

#endif
