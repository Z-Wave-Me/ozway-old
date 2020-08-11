//
//  CommandClassesPublic.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 2/1/12.
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

#ifndef zway_command_classes_public_h
#define zway_command_classes_public_h


// Command Class Basic (0x20/32) //
// V1 S+C //
// The Basic Command Class is the wildcard command class.
// Almost all Z-Wave devices support this command class but they interpret it's commands in different ways.
// A thermostat will handle a Basic Set Command in a different way than a Dimmer but both accept the Basic Set command and act.
// Used for generic interoperability between devices.
// You should always use more specific Command Classes where possible.
//
// @DH	level			Generic switching level of the device controlled

// Send Basic Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_basic_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Basic Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: value
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_basic_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Wakeup (0x84/132) //
// V2 C //
// Allows to manage periodical wakeup of sleeping battery operated device.
// Upon wakeup device will notify one node listed in nodeId.
//
// NB! If the device can wake up by interrupt (user interaction, button press, sensor trigger), it might happen that the device never wakes up.
// This can happen if you wake up the device by interrupe each time before internal chip wakeup period (usually from 1 to 4 minutes) reaches.
// (Z-Wave chip can not count for remaining time to next wakeup, so will restart timer again).
// This means that strictly speaking you can not rely on long time no wake up as an indicator of lost/damaged device or battery empty.
//
// NB! To save battery it is recommended to tune wakeup period to one week or even more for devices that do only need to report battery on wakeup (remote controls).
// For sensors it is recommended to have at least one hour wakeup period.
//
// @DH	interval	Wakeup interval in seconds
// @DH	nodeId		Node to notify about wakeup
// @DH	min		Minimal possible wakeup interval
// @DH	max		Maximal possible wakeup interval
// @DH	default		Factory default wakeup interval
// @DH	step		Step for wakeup interval (values are rounded to next or previous step)
// @DH	lastWakeup	Last time the device has sent us wake notification (Unix timestamp)
// @DH	lastSleep	Last time the device was sent into sleep mode (Unix timestamp)

// Send Wakeup Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: interval and nodeId updated
//
ZWEXPORT ZWError zway_cc_wakeup_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Wakeup CapabilityGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: min, max, default, step updated
//
ZWEXPORT ZWError zway_cc_wakeup_capabilities_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Wakeup NoMoreInformation (Sleep)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: lastSleep updated
ZWEXPORT ZWError zway_cc_wakeup_sleep(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Wakeup Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: interval
// Wakeup interval in seconds
//
// @param: notification_node_id
// Node Id to be notified about wakeup
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: interval and nodeId updated
//
ZWEXPORT ZWError zway_cc_wakeup_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int interval, ZWBYTE notification_node_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class NoOperation (0x00/0) //
// Used to check if device is reachable by sending empty packet.

// Send NoOperation empty packet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// This function is not exported into C and JS. Please use zway_device_send_nop() instead
// ZWEXPORT ZWError zway_cc_nop_send(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Battery (0x80/128) //
// V1 C //
// Allows monitoring the battery charging level of a device.
//
// @DH	last			Last battery level reported (0..100%)
// @DH	lastChange		Time (UNIX timestamp) when the battery was replaced last time (time of the moment when the value reported was way bigger than previous one)
// @DH	history			Subtree with history
// @DH		[% value]	Time when battery level reached this % value (0, 10, 20,... 100)

// Send Battery Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: last updated. lastChange updated if battery level is way higher than it was before, history updated if reached next 10% step
//
ZWEXPORT ZWError zway_cc_battery_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class ManufacturerSpecific (0x72/114) //
// V2 S+C //
// Reports vendor information, product type and ID and device serial number
//
// @DH	vendorId		Vendor ID assigned by Silicon Labs
// @DH	vendor			Vendor name
// @DH	productId		Product ID
// @DH	productType		Product Type ID
// @DH	serialNumber		Product Serial Number

// Send ManufacturerSpecific Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_manufacturer_specific_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ManufacturerSpecific Device Id Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// Device Id type to request
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_manufacturer_specific_device_id_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE type, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Proprietary (0x88/136) //
// V1 C //
// Allows to transfer manufacturer proprietary data. Data format is manufacturer specific.
//
// @DH	bytes		Binary bytes array of raw data

// Send Proprietary Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_proprietary_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Proprietary Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: length
// Length of data
//
// @param: data
// Data to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_proprietary_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE length, const ZWBYTE *data, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Configuration (0x70/112) //
// V1 C //
// Used to set certian configuration valeus that change the behavior of the device.
// Z-Wave requires that every device works out of the box without further configuration.
// However different configuration value significantly enhance the value a device.
// Z-Wave does not provide any information about the configuration values by wireless commands.
// User have to look into the device manual to learn about configuration parameters.
// The Device Description Record (ZDDX), incoprotated by Z-Way gives information about valid parameters and the meaning of the values to be set.
//
// @DH	[paramId]	Configuration parameter subtree.
// @DH		val	Value assigned
// @DH		size	Size of that parameter (1, 2 or 4 bytes)

// Send Configuration Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: parameter
// Parameter number (from 1 to 255)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: parameter subtree updated or created if absent
//
ZWEXPORT ZWError zway_cc_configuration_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE parameter, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Configuration Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: parameter
// Parameter number (from 1 to 255)
//
// @param: value
// Value to be sent (negative and positive values are accepted, but will be stripped to size)
//
// @param: size
// @default: 0
// Size of the value (1, 2 or 4 bytes). Use 0 to guess from previously reported value if any
// 0 means use size previously obtained Get
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: parameter subtree updated or created if absent
//
ZWEXPORT ZWError zway_cc_configuration_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE parameter, int value, ZWBYTE size, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Configuration SetDefault
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: parameter
// Parameter number to be set to device default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: parameter subtree updated or created if absent
//
ZWEXPORT ZWError zway_cc_configuration_set_default(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE parameter, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SensorBinary (0x30/48) //
// V2 C //
// Allows receive binary sensor states
//
// @DH	typemask			Internal. Bit mask of the supported types
// @DH	[sensorType]			Subtree for sensor type Id
// @DH		sensorTypeString	Description of sensor type
// @DH		level			Triggered/idle status

// Send SensorBinary Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: sensorType
// Type of sensor to query information for
// @default: -1
// 0xFF to query information for the first available sensor type
// -1 to query information for all supported sensor types
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: sensorType subtree updated
//
ZWEXPORT ZWError zway_cc_sensor_binary_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int sensorType, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Association (0x85/133) //
// V2 S+C //
// Allows to manage the association groups: adding and removing nodeIDs in the association groups.
// @DH	groups			Number of association groups in the device
// @DH	[groupId]		Group subtree, where groupId = 1..groups
// @DH		max		Number of nodes the group can hold
// @DH		nodes		Array with nodes in the group
// @DH		nodesToFollow	Internal
// @DH	specificGroup		Number of specific association groups in the device

// Send Association Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// @default: 0
// Group Id (from 1 to 255)
// 0 requests all groups
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Subtree corresponding to the group updated
//
ZWEXPORT ZWError zway_cc_association_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Association Set (Add)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: include_node
// Node to be added to the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Subtree corresponding to the group updated
//
ZWEXPORT ZWError zway_cc_association_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE include_node, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Association Remove
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: exclude_node
// Node to be removed from the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Subtree corresponding to the group updated
//
ZWEXPORT ZWError zway_cc_association_remove(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE exclude_node, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Association GroupingsGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Update number of supported groups and interview all groups
//
ZWEXPORT ZWError zway_cc_association_groupings_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Meter (0x32/50) //
// V4 C //
// Allows to read different kind of meters.
// Z-Wave differentiates different meter types and different meter scales.
// Please refer to the file translations/Scales.xml for details about possible meter types and values.
//
// @DH	scalemask			Internal. Bit mask with supported scales
// @DH	resettable			Flag to indicate of the meter can be resetted
// @DH	[scaleId]			Meter scale subtree
// @DH		scale			Meter scale id
// @DH		scaleString		Meter scale name
// @DH		sensorType		Sensor type id
// @DH		sensorTypeString	Sensor type name
// @DH		val			Meter value
// @DH		ratetype		Rate type
// @DH		delta			Delta from the last value requested
// @DH		previous		Previous value requested

// Send Meter Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: scale
// @default: -1
// Desired scale
// -1 for all scales
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: scale subtree updated
//
ZWEXPORT ZWError zway_cc_meter_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int scale, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Meter Reset
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: scale subtree updated
//
ZWEXPORT ZWError zway_cc_meter_reset(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Meter SupportedGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_supported(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Meter Pulse (0x35/53) //
// V1 C //
// Allows to gather information from pulse meters
//
// @DH	val		Meter pulse value

// Send MeterPulse Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_pulse_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SensorMultilevel (0x31/49) //
// V11 C //
// Allows to read different kind of sensor.
// Z-Wave differentiates different sensor types and different scales of this sensor.
// Please refer to the file /translations/scales.xml for details about possible sensor types and values.
//
// @DH	typemask			Internal. Bit mask of the supported types
// @DH	[sensorTypeId]			Subtree for sensor type Id
// @DH		sensorTypeString	Description of sensor type
// @DH		scale			Scale Id
// @DH		scaleString		Scale description
// @DH		val			Value
// @DH		size			Internal. Size of the value (1, 2 or 4 bytes)
// @DH		precision		Internal. Precision used in value (number of digits after decimal dot)
// @DH		deviceScale		Internal. Scale Id on the device's side (if local conversion is used, like C->F)

// Send SensorMultilevel Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: sensor_type
// @default: -1
// Type of sensor to be requested.
// -1 means all sensor types supported by the device
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: sensorTypeId subtree updated
//
ZWEXPORT ZWError zway_cc_sensor_multilevel_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int sensor_type, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Sensor Configuration (0x9e/158) //
// V1 C //
// Allows to configure senors specific configuration like trigger level.
// Works in conjunction with SensorMultilevel Command Class.
// In modern devices replaced by Configuration Command Class.
//
// @DH	sensorType			Sensor type Id
// @DH	sensorTypeString		Sensor type descirption
// @DH	val				Trigger value
// @DH	scale				Scale of trigger value
// @DH	scaleString			Scale description
// @DH	size				Internal. Size of the value (1, 2 or 4 bytes)
// @DH	precision			Internal. Precision used in value (number of digits after decimal dot)

// Send SensorConfiguration Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: all dataholders are updated
//
ZWEXPORT ZWError zway_cc_sensor_configuration_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SensorConfiguration Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Value set mode
//
// @param: value
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: all dataholders are updated
//
ZWEXPORT ZWError zway_cc_sensor_configuration_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, float value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SwitchAll (0x27/39) //
// V1 S+C //
// Controls the behavior of a actuator on Switch All commands.
// Also allows to send Switch All commands.
//
// @DH	mode			Which type of SwitchAll On/Off commands to react on: 0 for none, 1 to reacto on Off only, 2 to react on On only, 255 to react on both
// @DH	onOff			Allows to trigger SwitchAll On/Off commands from other devices. Set to False on Off command received and True on On command.

#define SWITCH_ALL_SET_EXCLUDED_FROM_THE_ALL_ON_ALL_OFF_FUNCTIONALITY            0x00
#define SWITCH_ALL_SET_EXCLUDED_FROM_THE_ALL_ON_FUNCTIONALITY_BUT_NOT_ALL_OFF    0x01
#define SWITCH_ALL_SET_EXCLUDED_FROM_THE_ALL_OFF_FUNCTIONALITY_BUT_NOT_ALL_ON    0x02
#define SWITCH_ALL_SET_INCLUDED_IN_THE_ALL_ON_ALL_OFF_FUNCTIONALITY              0xFF

// Send SwitchAll Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: mode updated
//
ZWEXPORT ZWError zway_cc_switch_all_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchAll Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// SwitchAll Mode: see definitions below
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: mode updated
//
ZWEXPORT ZWError zway_cc_switch_all_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchAll Set On
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_all_set_on(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchAll Set Off
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_all_set_off(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SwitchBinary (0x25/37) //
// V1 S+C //
// Allows to control On/Off switches, actuators, electrical power switches and trap On/Off control commands from other devices
//
// @DH	level			State: False for Off, True for On

// Send SwitchBinary Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_switch_binary_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchBinary Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: value
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_switch_binary_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBOOL value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SwitchMultilevel (0x26/38) //
// V1 S+C //
// Allows to control all actuators with multilevel switching functions, primarily Dimmers and Motor Controlling devices as well as trap dim events sent by remotes.
//
// @DH	level			State 0...99 = 0...100%, 255 for On on last value (or on maximum - device specific)
// @DH	startChange		Dimming up or down. Updated on dimming start. Allows to trap events from remotes to controller.
// @DH	stopChange		Updated on dimming end. Allows to trap events from remotes to controller.
// @DH	prevLevel		Internal
// @DH	primary			Unused
// @DH	secondary		Unsued

// Send SwitchMultilevel Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_switch_multilevel_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchMultilevel Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: level
// Level to be set
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01...0x7f in seconds
//  0x80...0xfe in minutes mapped to 1...127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_switch_multilevel_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE level, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchMultilevel StartLevelChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: dir
// Direction of change: 0 to incrase, 1 to decrase
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01...0x7f in seconds
//  0x80...0xfe in minutes mapped to 1...127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: ignoreStartLevel
// @default: TRUE
// If set to True, device will ignore start level value and will use it's curent value
//
// @param: startLevel
// @default: 50
// Start level to change from
//
// @param: incdec
// @default: 0
// Increment/decrement type for step:
//  0 Increment
//  1 Decrement
//  2 Reserved
//  3 No Inc/Dec
//
// @param: step
// @default: 0xff
// Step to be used in level change in percentage
// 0...99 mapped to 1...100%
// 0xff uses device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_switch_multilevel_start_level_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE dir, ZWBYTE duration, ZWBOOL ignoreStartLevel, ZWBYTE startLevel, ZWBYTE incdec, ZWBYTE step, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchMultilevel StopLevelChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level updated
//
ZWEXPORT ZWError zway_cc_switch_multilevel_stop_level_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class MultiChannelAssociation (0x8e/142) //
// V3 S+C //
// This is an extention to the Association Command Class.
// It follows the same logic as the Association Command Class and has the same commands but accepts different instance values.
//
// @DH	groups				Number of association groups in the device (can be smaller than the number of groups in Association)
// @DH	[groupId]			Group subtree, where groupId = 1..groups
// @DH		max			Number of nodes/instances the group can hold
// @DH		nodesInstances		Array with nodes/instances in the group. Each pair is represented by two elements (node, instance).
// @DH		nodesInstancesToFollow	Internal

// Send MultiChannelAssociation Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// @default: 0
// Group Id (from 1 to 255)
// 0 requests all groups
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Subtree corresponding to the group updated
//
ZWEXPORT ZWError zway_cc_multichannel_association_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannelAssociation Set (Add)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: include_node
// Node to be added to the group
//
// @param: include_instance
// Instance of the node to be added to the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Subtree corresponding to the group updated
//
ZWEXPORT ZWError zway_cc_multichannel_association_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE include_node, ZWBYTE include_instance, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannelAssociation Remove
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: exclude_node
// Node to be removed from the group
//
// @param: exclude_instance
// Instance of the node to be removed from the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Subtree corresponding to the group updated
//
ZWEXPORT ZWError zway_cc_multichannel_association_remove(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE exclude_node, ZWBYTE exclude_instance, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannelAssociation GroupingsGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_association_groupings_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class MultiChannel (0x60/96) //
// V4 S+C //
// Allows to communicate with internal parts of device called channels or instances.
// Implemented transparently by the library.
//
// @DH	endPoints			Number of endpoints
// @DH		[endPointId]		Endpoint ID
// @DH	aggregated			Number of aggregated endpoints
// @DH		[endPointId]		Aggregated endpoint ID (numbering starts from endPoints + 1)
// @DH	dynamic				Flag describing if endpoins are dynamic (their number and type can change over time)
// @DH	identical			Internal. Flag describing if endpoins are  identical
// @DH	myInstance			Internal
// @DH	doneIds				Internal

// Send MultiChannel Get (MultiInstance V1 command)
// Reports number of channels supporting a defined Command Class
// Depricated by MutliChannel V2, needed for old devices only
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: cc_id
// Command Class Id in question
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE cc_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Endpoint Find
// Note that MultiChannel EndpointFind Report is not supported as useless. But one can still trap the response packet in logs.
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: generic
// Generic type in search
//
// @param: specific
// Specific type in search
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_endpoint_find(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE generic, ZWBYTE specific, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Endpoint Get
// Get the number of available endpoints
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_endpoint_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Capabilities Get
// Request information about the specified endpoint
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: endpoint
// Endpoint in question
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_capabilities_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE endpoint, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Aggregated Members Get
// Request information about endpoints in the specified aggregated endpoint (v4 and above)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: endpoint
// Aggregated endpoint in question
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_aggregated_members_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE endpoint, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Node Naming (0x77/119) //
// V1 S+C //
// Allows assigning a readable string for a name and a location to a physical device.
// The two strings are stored inside the device and can be obtained upon request.
// There are no restrictions to the name except the maximum length up to 16 characters.
//
// @DH	nodename		Node name
// @DH	nameEncoding		NodeName encoding
// @DH	location		Location
// @DH	locationEncoding	Location encoding

// Send NodeNaming GetName and GetLocation
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: nodename, nameEncoding, location and locationEncoding updated
//
ZWEXPORT ZWError zway_cc_node_naming_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming GetName
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: nodename and nameEncoding updated
//
ZWEXPORT ZWError zway_cc_node_naming_get_name(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming GetLocation
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: location and locationEncoding updated
//
ZWEXPORT ZWError zway_cc_node_naming_get_location(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming SetName
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: name
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: nodename and nameEncoding updated
//
ZWEXPORT ZWError zway_cc_node_naming_set_name(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWCSTR name, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming SetLocation
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: location
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: location and locationEncoding updated
//
ZWEXPORT ZWError zway_cc_node_naming_set_location(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWCSTR location, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat SetPoint (0x43/67) //
// V3 C //
// Allows to set a certain setpoint to a thermostat (set temperature to maintain).
// The command class can be applied to different kind of thermostats (heating, cooling, ...), hence it has various modes.
//
// @DH	[modeId]			Subtree for mode
// @DH		modeName		Mode description
// @DH		scale			Scale Id
// @DH		scaleString		Scale description
// @DH		val			Temperature to maintain
// @DH		setVal			Last set temperature to maintain (might differ from val until thermostat wakeup)
// @DH		min			Minimal temperature value supported by the device
// @DH		max			Maximal temperature value supported by the device
// @DH		size			Internal. Size of the value (1, 2 or 4 bytes)
// @DH		precision		Internal. Precision used in value (number of digits after decimal dot)
// @DH		deviceScale		Internal. Scale Id on the device side (if local conversion is used, like C->F)
// @DH		deviceScaleString	Internal. Scale description of the device
// @DH	modemask			Internal. Bit mask with supported modes
// @DH	danfossBugFlag			Internal

// Send ThermostatSetPoint Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// @default: -1
// Thermostat Mode
// -1 requests for all modes
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: modeId subtree updated
//
ZWEXPORT ZWError zway_cc_thermostat_setpoint_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatSetPoint Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Thermostat Mode
//
// @param: value
// temperature
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: modeId subtree updated
//
ZWEXPORT ZWError zway_cc_thermostat_setpoint_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int mode, float value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Mode (0x40/64) //
// V3 C //
// Allows to switch a heating/cooling actuator in different modes.
//
// @DH	modemask		Internal. Bit mask with supported modes
// @DH	mode			Current mode
// @DH	[modeId]		Mode subtree
// @DH		modeName	Mode description

// Send ThermostatMode Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// report: mode updated
//
ZWEXPORT ZWError zway_cc_thermostat_mode_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatMode Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Thermostat Mode
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// report: mode updated
//
ZWEXPORT ZWError zway_cc_thermostat_mode_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Fan Mode (0x44/68) //
// V4 C //
// Allows to controls fan modes in thermostats.
//
// @DH	modemask		Internal. Bit mask with supported modes
// @DH	mode			Current mode
// @DH	[modeId]		Mode subtree
// @DH		modeName	Mode description
// @DH	on			Reports if fan is currently On (True) or Off (False)

// Send ThermostatFanMode Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: mode and on updated
//
ZWEXPORT ZWError zway_cc_thermostat_fan_mode_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatFanMode Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: on
// TRUE to turn fan on (and set mode), FALSE to comletely turn off (mode is ignored)
//
// @param: mode
// Thermostat Fan Mode
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: mode and on updated
//
ZWEXPORT ZWError zway_cc_thermostat_fan_mode_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBOOL on, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Fan State (0x45/69) //
// V2 C //
// Allows to determine the operating state of the fan.
// V2 is not yet implemented.
//
// @DH	state			Fan current state (0 Off, 1 Running)

// Send ThermostatFanState Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: state and on updated
//
ZWEXPORT ZWError zway_cc_thermostat_fan_state_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Operating State (0x42/66) //
// V2 C //
// Allows to determine the operating state of the thermostat and state change history.
//
// @DH	state				Current operation state
// @DH	statemask			Internal. Bit mask of supported logs for each state
// @DH	[stateId]			Subtree with state log info
// @DH		today			Number of minutes thermostat was in this state today (since 0:00)
// @DH		yesterday		Number of minutes thermostat was in this state yesterday (since 0:00)

// Send ThermostatOperatingState Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: state updated
//
ZWEXPORT ZWError zway_cc_thermostat_operating_state_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatOperatingState Logging Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: state
// State number to get logging for
// 0 to get log for all supported states
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: stateId subtree updated updated
//
ZWEXPORT ZWError zway_cc_thermostat_operating_state_logging_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE state, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Alarm Sensor (0x9c/156) //
// V1 C //
// Deprecated Command Class. Now Alarm/Notification is used instead.
//
// @DH	alarmMap		Internal. Bit mask of supported alarm types
// @DH	alarms			Unused
// @DH	[alarmTypeId]		Alarm type subtree
// @DH		srcId		Source of event
// @DH		sensorState	Alarm state
// @DH		sensorTime	Alarm time (according to the sender)
// @DH		typeString	Name of alarm type

// Send AlarmSensor SupportedGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: List of supported types updated
//
ZWEXPORT ZWError zway_cc_alarm_sensor_supported_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send AlarmSensor Get
// Requests the status of the alarm sensor of a given type
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// @default: -1
// Alarm type to get
// -1 means get all types
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Alarm type subtree updated
//
ZWEXPORT ZWError zway_cc_alarm_sensor_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int type, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Door Lock (0x62/98) //
// V2 C //
// Allows to operate an electronic door lock.
// This Command Class is ALWAYS encapsulated in Security
//
// Door lock modes are the following:
//
// - 0x00 Door Unsecured (Open)
// - 0x01 Door Unsecured with timeout
// - 0x10 Door Unsecured for inside Door Handles
// - 0x11 Door Unsecured for inside Door Handles with timeout
// - 0x20 Door Unsecured for outside Door Handles
// - 0x21 Door Unsecured for outside Door Handles with timeout
// - 0xFE Door/Lock Mode Unknown (bolt not fully retracted/engaged)
// - 0xFF Door Secured (closed)
//
// @DH	mode			Operating mode of the lock
// @DH	insideMode		Bit mask describing if a specific handles (1..4) can open the door from inside
// @DH	outsideMode		Bit mask describing if a specific handles (1..4) can open the door from outside
// @DH	lockMinutes		Time remaind before autolock (minutes, 0xFE for no autolock)
// @DH	lockSeconds		Time remaind before autolock (seconds, 0xFE for no autolock)
// @DH	condition		Bit mask describing lock components: bit 0: Door Open(0)/Close(1), bit 1: Bolt Locked(0)/Unlocked(1), bit 2: Latch Open(0)/Close(1)
// @DH	insideState		Bit mask describing if a specific handles (1..4) can open the door from inside
// @DH	outsideState		Bit mask describing if a specific handles (1..4) can open the door from outside
// @DH	timeoutMinutes		Timeout for autolock (minutes, 0xFE for no autolock)
// @DH	timeoutSeconds		Timeout for autolock (seconds, 0xFE for no autolock)
// @DH	opType			0x01 for constant operation, 0x02 for autolock

// Send DoorLock Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: mode, insideMode, outsideMode, lockMinutes, lockSeconds and condition updated
//
ZWEXPORT ZWError zway_cc_door_lock_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send DoorLock Configuration Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: insideState, outsideState, timeoutMinutes, timeoutSeconds, opType updated
//
ZWEXPORT ZWError zway_cc_door_lock_configuration_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send DoorLock Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Lock mode
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: mode, insideMode, outsideMode, lockMinutes, lockSeconds and condition updated
//
ZWEXPORT ZWError zway_cc_door_lock_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send DoorLock Configuration Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: opType
// Operation type
//
// @param: outsideState
// State of outside door handle
//
// @param: insideState
// State of inside door handle
//
// @param: lockMin
// Lock after a specified time (minutes part)
//
// @param: lockSec
// Lock after a specified time (seconds part)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: insideState, outsideState, timeoutMinutes, timeoutSeconds, opType updated
//
ZWEXPORT ZWError zway_cc_door_lock_configuration_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE opType, ZWBYTE outsideState, ZWBYTE insideState, ZWBYTE lockMin, ZWBYTE lockSec, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Door Lock Logging (0x4C/76) //
// V1 C //
// Allows to receive reports about all successful and failed activities of the electronic door lock
//
// Event types are the following:
// - 1 Lock Command: Keypad access code verified lock command
// - 2 Unlock Command: Keypad access code verified unlock command
// - 3 Lock Command: Keypad lock button pressed
// - 4 Unlock command: Keypad unlock button pressed
// - 5 Lock Command: Keypad access code out of schedule
// - 6 Unlock Command: Keypad access code out of schedule
// - 7 Keypad illegal access code entered
// - 8 Key or latch operation locked (manual)
// - 9 Key or latch operation unlocked (manual)
// - 10 Auto lock operation
// - 11 Auto unlock operation
// - 12 Lock Command: Z-Wave access code verified
// - 13 Unlock Command: Z-Wave access code verified
// - 14 Lock Command: Z-Wave (no code)
// - 15 Unlock Command: Z-Wave (no code)
// - 16 Lock Command: Z-Wave access code out of schedule
// - 17 Unlock Command Z-Wave access code out of schedule
// - 18 Z-Wave illegal access code entered
// - 19 Key or latch operation locked (manual)
// - 20 Key or latch operation unlocked (manual)
// - 21 Lock secured
// - 22 Lock unsecured
// - 23 User code added
// - 24 User code deleted
// - 25 All user codes deleted
// - 26 Master code changed
// - 27 User code changed
// - 28 Lock reset
// - 29 Configuration changed
// - 30 Low battery
// - 31 New Battery installed
//
// @DH	maxRecords		Maximum number of records the lock can store. Olded records are reused first.
// @DH	[recordId]		Subtree storing log record
// @DH		time		Time of the event
// @DH		event		Event type
// @DH		uId		UserID (from UserCode Command Class)
// @DH		eventString	Event type description

// Send DoorLockLogging Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: record
// @default: 0
// Record number to get, or 0 to get last records
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: record subtree updated
//
ZWEXPORT ZWError zway_cc_door_lock_logging_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE record, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class User Code (0x63/99) //
// V1 C //
// Allows to define individual user entry code in electrnic door lock
//
// @DH	maxUsers		Maximum number of supported users
// @DH	[userId]		User subtree
// @DH		code		User code
// @DH		status		Status of the user: 0 for available (no code set), 1 for occupied (code set), 2 for reserved by administrator
// @DH		hasCode		Flag if a valid code is set (in case device reports occupied, but code is not valid (less than 4 symbols) or code not set but old is still reported by the device)

// Send UserCode Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// @default: -1
// User index to get code for (1...maxUsers)
// -1 to get codes for all users
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: userId subtree updated
//
ZWEXPORT ZWError zway_cc_user_code_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send UserCode Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User index to set code for (1...maxUsers)
// 0 means set for all users
//
// @param: code
// Code to set (4...10 characters long)
//
// @param: status
// Code status to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: userId subtree updated
//
ZWEXPORT ZWError zway_cc_user_code_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWCSTR code, ZWBYTE status, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send UserCode Set (raw)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User index to set code for (1...maxUsers)
// 0 means set for all users
//
// @param: length
// Length of code in bytes
//
// @param: code
// Code to set (4...10 bytes long)
//
// @param: status
// Code status to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: userId subtree updated
//
ZWEXPORT ZWError zway_cc_user_code_set_raw(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE length, const ZWBYTE *code, ZWBYTE status, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Time (0x8a/138) //
// V2 S+C //
// Allows to report to devices in Z-Wave network time and date as well as time zone offset and daylight savings parameters.
// The data formats are based on the International Standard ISO 8601

// Send Time TimeGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_time_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Time DateGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_date_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Time TimeOffsetGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_offset_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Time Parameters (0x8b/139) //
// V1 C //
// Used to set date and time.
// Time zone offset and daylight savings may be set in the Time Command Class.
// The data formats are based on the International Standard ISO 8601.

// Send TimeParameters Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_parameters_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send TimeParameters Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_parameters_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Clock (0x81/129) //
// V1 S+C //
// Sync clock on the device with controller system clock

// Send Clock Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: reported value ignored
//
ZWEXPORT ZWError zway_cc_clock_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Clock Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_clock_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Scene Activation (0x2B/43) //
// V1 S+C //
// Allows to activate scenes on devices and trap scene activation events from remotes
//
// @DH	currentScene		Scene activated from remote
// @DH	dimmingDuration		Dimming duration for the activated scene

// Send SceneActivation Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: sceneId
// Scene Id
//
// @param: dimmingDuration
// @default: 0xff
// Dimming duration
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_scene_activation_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE sceneId, ZWBYTE dimmingDuration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Scene Controller Conf (0x2d/45) //
// V1 C //
// Allows to set scene Id to be activated using SceneActivation Command Class on a remote
//
// @DH	[groupId]		Subtree for a given association group number (defined by Association Command Class)
// @DH		scene		Scene to activate for all devices in the group
// @DH		duration	Duration for scene activation

// Send SceneControllerConf Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group
// @default: 0
// Group Id
// 0 requests all groups
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: group subtree updated
//
ZWEXPORT ZWError zway_cc_scene_controller_conf_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SceneControllerConf Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group
// Group Id
//
// @param: scene
// Scene Id
//
// @param: duration
// @default: 0x0
// Duration
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: group subtree updated
//
ZWEXPORT ZWError zway_cc_scene_controller_conf_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group, ZWBYTE scene, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Scene Actuator Conf (0x2C/44) //
// V1 C //
// Allows to configure actuators to set specified level on a given scene activation by SceneActivation Command Class
//
// @DH	[sceneId]			Subtree for scene
// @DH		level			Level to set on scene activation
// @DH		dimming			Default dimming duration to use
// @DH	currentScene			Currently activated scene

// Send SceneActuatorConf Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: scene
// @default: 0
// Scene Id
// 0 means get current scene
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: scene subtree updated, currentScene updated (if scene = 0)
//
ZWEXPORT ZWError zway_cc_scene_actuator_conf_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE scene, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SceneActuatorConf Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: scene
// Scene Id
//
// @param: level
// Level
//
// @param: dimming
// @default: 0xff
// Dimming
//
// @param: override
// @default: TRUE
// If false then the current settings in the device is associated with the Scene Id. If true then the Level value is used
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: scene subtree updated
//
ZWEXPORT ZWError zway_cc_scene_actuator_conf_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE scene, ZWBYTE level, ZWBYTE dimming, ZWBOOL override, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Indicator (0x87/135) //
// V1 C //
// Operates the indicator on the device if available.
// Can be used to identify a device or use the indicator for special purposes (show away/at home mode).
//
// @DH	stat		Status of the indicator

// Send Indicator Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: stat updated
//
ZWEXPORT ZWError zway_cc_indicator_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Indicator Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: val
// Value to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: stat updated
//
ZWEXPORT ZWError zway_cc_indicator_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE val, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Protection (0x75/117) //
// V2 C //
// Allows to disable local and RF control of the device.
//
// @DH	state			Local control state (0 = Unprotected, 1 = Protected by sequence, 2 = Protected)
// @DH	rfState			Control via RF state (0 = Unprotected, 1 = No RF control, 2 = No RF response at all)
// @DH	exclusive		Flag describing if exclusive control via RF is supported
// @DH	timeout			Flag describing if timeout of protection of control via RF is supported
// @DH	stateCap		Requires Z-Wave specification re-read. Please contact Z-Wave.Me support
// @DH	rfStateCap		Requires Z-Wave specification re-read. Please contact Z-Wave.Me support
// @DH	exclusiveCap		Requires Z-Wave specification re-read. Please contact Z-Wave.Me support
// @DH	timeoutCap		Requires Z-Wave specification re-read. Please contact Z-Wave.Me support

// Send Protection Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: state, rfState updated
//
ZWEXPORT ZWError zway_cc_protection_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: state
// Local control protection state
//
// @param: rfState
// @default: 0
// RF control protection state
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: state and rfState updated
//
ZWEXPORT ZWError zway_cc_protection_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE state, ZWBYTE rfState, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Exclusive Control Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_exclusive_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Exclusive Control Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: controlNodeId
// Node Id to have exclusive control over destination node
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_exclusive_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE controlNodeId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Timeout Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_timeout_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Timeout Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: timeout
// Timeout in seconds
// 0 is no timer set
// -1 is infinite timeout
// max value is 191 minute (11460 seconds)
// values above 1 minute are rounded to 1 minute boundary
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_timeout_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int timeout, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Schedule Entry Lock (0x4e/78) //
// V3 C //
// Allows to define individual time intervals for access to a door lock per user.
// Refers to users defined by User Code Command Class.
//
// @DH	weekDaySlots				Number of weekday slots supported
// @DH	yearSlots				Number of date slots supported
// @DH	[userId]				Subtree for userId
// @DH		Weekday				Subtree for weekday schedule
// @DH			[slotId]		Subtree slotId
// @DH				dayOfWeek	Day of week
// @DH				startHour	Start hour
// @DH				startMinute	Start minute
// @DH				stopHour	Stop hour
// @DH				stopMinute	Stop minute
// @DH		Year				Subtree for date schedule
// @DH			[slotId]		Subtree slotId
// @DH				startYear	Start year
// @DH				startMonth	Start month
// @DH				startDay	Start day
// @DH				startHour	Start hour
// @DH				startMinute	Start minute
// @DH				stopYear	Stop year
// @DH				stopMonth	Stop month
// @DH				stopDay		Stop day
// @DH				stopHour	Stop hour
// @DH				stopMinute	Stop minute

// Send ScheduleEntryLock Enable(All)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to enable/disable schedule for
// 0 to enable/disable for all users
//
// @param: enable
// TRUE to enable schedule, FALSE otherwise
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_enable(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBOOL enable, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Weekday Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to get schedule for
// 0 to get for all users
//
// @param: slot
// Slot to get schedule for
// 0 to get for all slots
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: userId->Weekday->slotId subtree updated
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_weekday_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Weekday Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to set schedule for
//
// @param: slot
// Slot to set schedule for
//
// @param: dayOfWeek
// Weekday number (0..6)
// 0 = Sunday
// ...
// 6 = Saturday
//
// @param: startHour
// Hour when schedule starts (0..23)
//
// @param: startMinute
// Minute when schedule starts (0..59)
//
// @param: stopHour
// Hour when schedule stops (0..23)
//
// @param: stopMinute
// Minute when schedule stops (0..59)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: userId->Weekday->slotId subtree updated
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_weekday_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZWBYTE dayOfWeek, ZWBYTE startHour, ZWBYTE startMinute, ZWBYTE stopHour, ZWBYTE stopMinute, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Year Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to enable/disable schedule for
// 0 to get for all users
//
// @param: slot
// Slot to get schedule for
// 0 to get for all slots
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: userId->Year->slotId subtree updated
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_year_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Year Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to set schedule for
//
// @param: slot
// Slot to set schedule for
//
// @param: startYear
// Year in current century when schedule starts (0..99)
//
// @param: startMonth
// Month when schedule starts (1..12)
//
// @param: startDay
// Day when schedule starts (1..31)
//
// @param: startHour
// Hour when schedule starts (0..23)
//
// @param: startMinute
// Minute when schedule starts (0..59)
//
// @param: stopYear
// Year in current century when schedule stops (0..99)
//
// @param: stopMonth
// Month when schedule stops (1..12)
//
// @param: stopDay
// Day when schedule stops (1..31)
//
// @param: stopHour
// Hour when schedule stops (0..23)
//
// @param: stopMinute
// Minute when schedule stops (0..59)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: userId->Year->slotId subtree updated
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_year_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZWBYTE startYear, ZWBYTE startMonth, ZWBYTE startDay, ZWBYTE startHour, ZWBYTE startMinute, ZWBYTE stopYear, ZWBYTE stopMonth, ZWBYTE stopDay, ZWBYTE stopHour, ZWBYTE stopMinute, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Climate Control Schedule (0x46/70) //
// V1 S+C //
// Obsolete but still partly implemented for legacy support.
//
// @DH	overrideType		Type of current override
// @DH	overrideState		State of override

// Send ClimateControlSchedule Override Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_climate_control_schedule_override_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ClimateControlSchedule Override Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: overrideType
// Override type to set
// (0 – no override, 1 – temporary override, 2 – permanent override)
//
// @param: overrideState
// Override state
// -128 (0x80) ... -1 (0xFF): setpoint -12.8 ... -0.1 degrees
// 0 (0x00): setpoint
// 1 (0x01) ... 120 (0x78): setpoint +0.1 ... +12 degrees
// 121 (0x79): frost protection
// 122 (0x7A): energy saving
// 123 (0x7B) ... 126 (0x7D): reserved
// 127 (0x7F): unused
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_climate_control_schedule_override_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE overrideType, ZWBYTE overrideState, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class MeterTableMonitor (0x3D/61) //
// V2 C //
// Allows to read historical and accumulated values in physical units from a water meter or other metering device (gas, electric etc.) and thereby enabling automatic meter reading capabilities
//
// @DH	adminId					Meter administrator ID
// @DH	Id					Customer ID
// @DH	rateType				Type of rate (export or import)
// @DH	payMeter				Specifies the way the account is done
// @DH	meterType				Meter type
// @DH	meterTypeString				Meter description
// @DH	dataSetMask				Internal. Bit mask with type of data set supported
// @DH	dataSetHistoryMask			Internal. Bit mask with type of data set history supported
// @DH	maxHistory				Max number of records the device can store
// @DH	statusMask				Internal. Bit mask with type of events supported
// @DH	maxEvents				Max number of events the device can store
// @DH	[dataSetId]				Subtree for data set
// @DH		val				Meter value for this data set
// @DH		time				Time corresponding to the value
// @DH		scale				Scale ID
// @DH		scaleString			Scale desctiption
// @DH		history				Requires Z-Wave specification re-read. Please contact Z-Wave.Me support
// @DH	status					Subtree with statuses
// @DH		[statuseId]			Subtree with specific status ID
// @DH			statusString		Status descirption
// @DH			active			Requires Z-Wave specification re-read. Please contact Z-Wave.Me support
// @DH			time			Requires Z-Wave specification re-read. Please contact Z-Wave.Me support

// Send StatusTableMonitor Status Get for a range of dates
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: maxResults
// @default: 0
// Maximum number of entries to get from log
// 0 means all matching entries
//
// @param: startDate
// Start date and time (local UNIX time)
//
// @param: endDate
// End date and time (local UNIX time)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_status_date_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE maxResults, time_t startDate, time_t endDate, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send StatusTableMonitor Status Get for specified depth
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: maxResults
// @default: 0
// Number of entries to get from log
// 0 means current status only
// 0xFF means all entries
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_status_depth_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE maxResults, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send StatusTableMonitor Current Data Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: setId
// @default: 0
// Index of dataset to get data for
// 0 to get data for all supported datasets
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_current_data_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE setId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send StatusTableMonitor Historical Data Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: setId
// @default: 0
// Index of dataset to get data for
// 0 to get data for all supported datasets
//
// @param: maxResults
// @default: 0
// Maximum number of entries to get from log
// 0 means all matching entries
//
// @param: startDate
// Start date and time (local UNIX time)
//
// @param: endDate
// End date and time (local UNIX time)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_historical_data_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE setId, ZWBYTE maxResults, time_t startDate, time_t endDate, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Alarm (0x71/113) //
// V5 C //
// Also known as Notification Command Class.
// Used to report alarm events from binary sensors. Starting from version 3 all types are strictly defines:
// - 0x01 Smoke
// - 0x02 CO
// - 0x03 CO2
// - 0x04 Heat
// - 0x05 Water
// - 0x06 Access Control
// - 0x07 Burglar
// - 0x08 Power Management
// - 0x09 System
// - 0x0a Emergency
// - 0x0b Clock
//
// @DH	V1supported		boolean flag saying if version 1 (deprecated) is supported
// @DH	V1event 		structure to store V1 events
// @DH		alarmType	V1 alarm type
// @DH		level		V1 status
// @DH	typeMask		bit mask of supported alarm types
// @DH	[typeId]		subtree to store events of specific alarm types
// @DH		typeString	name of the alarm type
// @DH		status		flag with alarm status (alarm enabled/disabled)
// @DH		eventMask	bit mask of supported events of this alarm type
// @DH		event		last event ID
// @DH		eventString	last event name
// @DH		eventParameters	last event parameters
// @DH		eventSequence	internal

// Send Alarm Get
// Requests the status of a specific event of a specific alarm type.
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// @default: 0
// Type of alarm to get level for
// 0 to get level for all supported alarms (v2 and higher)
// 0xFF to get level for first supported alarm (v2 and higher)
//
// @param: event
// @default: 0
// Notification event to get level for
// This argument is ignored prior to Notification v3
// Must be 0 if type is 0xFF
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Alarm type subtree updated
//
ZWEXPORT ZWError zway_cc_alarm_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE type, ZWBYTE event, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Alarm Set (v2 and higher)
// Enable/disable alarms of a specific type.
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// Type of alarm to set level for
//
// @param: level
// Level to set (0x0 = off, 0xFF = on, other values are reserved)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: Alarm type subtree updated
//
ZWEXPORT ZWError zway_cc_alarm_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE type, ZWBYTE level, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class PowerLevel (0x73/115) //
// V1 S+C //
// Used to set device power level and to test the link to a other devices in the network
//
// @DH	level				Current power level (0 for normal power, 1..9 for -1..-9 dBm)
// @DH	timeout				Timeout of the power level set (after timeout the device turns back to normal power)
// @DH	[nodeId]			Subtree with report of a test with nodeId
// @DH		status			Current test status (0 = Failed, 1 = Successfully finished, 2 = In progress)
// @DH		totalFrames		Total frames sent
// @DH		acknowledgedFrames	Acknowledged frames from total sent

// Send PowerLevel Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level and timeout updated
//
ZWEXPORT ZWError zway_cc_power_level_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send PowerLevel Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: level
// Power level to set (from 0 to 9)
//
// @param: timeout
// Timeout in seconds
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: level and timeout updated
//
ZWEXPORT ZWError zway_cc_power_level_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE level, ZWBYTE timeout, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send PowerLevel Test Node Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: subtree with report for the given node updated
//
ZWEXPORT ZWError zway_cc_power_level_test_node_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send PowerLevel Test Node Set
// Starts sending specified number of NOP packets to a given device at a given power level.
// Once finished, unsolicited report MIGHT be sent by the device (at any time you can use TestNodeGet).
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: testNodeId
// Node to set test packets to
//
// @param: level
// Power level to use (from 0 to 9)
//
// @param: frameCount
// Number of test frames to send (from 1 to 65535)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: subtree with report for the given node updated
//
ZWEXPORT ZWError zway_cc_power_level_test_node_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE testNodeId, ZWBYTE level, int frameCount, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Z-Wave Plus Info (0x5E/94) //
// V2 S+C //
// Describes device Z-Wave Plus role and type
//
// @DH	plusVersion			Z-Wave Plus version
// @DH	roleType			Z-Wave Plus role type
// @DH	roleTypeString			Z-Wave Plus role type description
// @DH	nodeType			Z-Wave Plus node type
// @DH	installerIcon			Icon for installer
// @DH	userIcon			Icon for user

// Send ZWave+ Info Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_zwave_plus_info_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Firmware Update (0x7A/122) //
// V4 C //
// Allows to update firmware of the device (OTA, Over-The-Air upgrade)
//
// @DH	upgradeable		Flag representing if the firmware is upgradable
// @DH	firmwareCount		Number of firmwares that can be updated using OTA (for multi chip devices, 0 is Z-Wave chip only)
// @DH	updateStatus		Indicated the status of the update process
// @DH	waitTime		Time the device will take before rebooting with newly upgraded firmware
// @DH	manufacturerId		Manufacturere ID
// @DH	firmwareId		Firmware Id
// @DH	firmware[n]		Firmware Id of firmware [n]
// @DH	checksum		Checksum of the firmware
// @DH	fragmentTransmitted	Number of fragments transmitted (useful to make progress bar)
// @DH	fragmentCount		Number of fragments to be transmitted in total (useful to make progress bar)
// @DH	fragmentSize		Internal
// @DH	firmwareData		Internal

// Send Firmware Metadata Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: upgradeable, firmwareCount, updateStatus, manufacturerId, manufacturerId, firmwareId, firmware[n], checksum updated
//
ZWEXPORT ZWError zway_cc_firmware_update_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Firmware Update Request Get
//
// On process start Z-Way sets fragmentCount:
//  devices.N.instances.0.commandClasses.122.data.fragmentCount = 3073 (0x00000c01)
// Then it asks the device to start the process. The device can refuse it (i.e. if local confirmation timed out).
// If confirmed, the device will send us a report with adjusted fragment size (if it wants Z-Way to send by smaller packets) and report "Ready" (updateStatus = 255, see below).
//  devices.N.instances.0.commandClasses.122.data.updateStatus = 255 (0x000000ff)
//  devices.N.instances.0.commandClasses.122.data.fragmentCount = 3277 (0x00000ccd)
// At this point fragmentTransmitted == 0
//  devices.N.instances.0.commandClasses.122.data.fragmentTransmitted =0
// Then device starts asking Z-Way for different packets. Z-Way will update fragmentTransmitted to allow track the process.
// Once done (fragmentCount == fragmentTransmitted), the device will send again a report if the flashing was successful. updateStatus contains the status: checksum error = 0, assemble error = 1, success, restart manually = 254, success, automatic restart = 255
// waitTime refers to the time device will take to reboot.
//  devices.N.instances.0.commandClasses.122.data.updateStatus = 255 (0x000000ff)
//  devices.N.instances.0.commandClasses.122.data.waitTime = 5 (0x00000005)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: manufacturerId
// Manufacturer Id (2 bytes)
//
// @param: firmwareId
// Firmware Id (2 bytes)
//
// @param: firmwareTarget
// Firmware target number (0 for main chip, 1..255 for additional chips)
// Used only for CC v3 and above
//
// @param: length
// Size of firmware image
//
// @param: data
// Firmware image data in binary format (use hex2bin to convert from Intel Hex)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @report: updateStatus, waitTime, fragmentCount, fragmentTransmitted updated
//
ZWEXPORT ZWError zway_cc_firmware_update_perform(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int manufacturerId, int firmwareId, ZWBYTE firmwareTarget, size_t length, const ZWBYTE *data, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Association Group Information (0x59/89) //
// V1 S+C //
// Describes association groups defined by Association Command Class and command sent to group members.
//
// @DH	[groupId]				Subtree for grouId
// @DH		groupName			Group name
// @DH		profile				Group profile Id
// @DH		mode				Internal. Reserved.
// @DH		eventCode			Internal. Reserved
// @DH		commands			Subtree for commands
// @DH			[commandClassId]	Command Class Id of the command sent to group members
// @DH				[commandId]	Command Id corresponding to Command Class Id
// @DH	dynamic					Flag describing if the list can change and periodic request to update information is suggested

// Send AGI Get Info
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: groupId
// Group Id to get info for (0 for all groups)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_group_information_get_info(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE groupId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send AGI Get Name
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: groupId
// Group Id to get info for (0 for all groups)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_group_information_get_name(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE groupId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send AGI Get Commands
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: groupId
// Group Id to get info for (0 for all groups)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_group_information_get_commands(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE groupId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SwitchColor (0x33/51) //
// V3 C //
// Allows to control color for multicolor lights including LED bulbs and LED strips.
// Device reports it's capabilities:
// - 0 Warm White (0x00...0xFF: 0...100%)
// - 1 Cold White (0x00:...0xFF: 0...100%)
// - 2 Red (0x00...0xFF: 0...100%)
// - 3 Green (0x00...0xFF: 0...100%)
// - 4 Blue (0x00...0xFF: 0...100%)
// - 5 Amber (for 6ch Color mixing) (0x00...0xFF: 0...100%)
// - 6 Cyan (for 6ch Color mixing) (0x00...0xFF: 0...100%)
// - 7 Purple (for 6ch Color mixing) (0x00...0xFF: 0...100%)
// - 8 Indexed Color (0x00...0x0FF: Color Index 0...255)
//
// @DH	capabilityMask			Internal. Bit mask with supported capabilities
// @DH	[capabilityId]			Subtree for capabilityId
// @DH		capabilityString	Capability description
// @DH		level			Level of capability

// Send SwitchColor Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: capabilityId subtree updated
//
ZWEXPORT ZWError zway_cc_switch_color_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id
//
// @param: state
// State to be set for the capability
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01...0x7f in seconds
//  0x80...0xfe in minutes mapped to 1...127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: capabilityId subtree updated
//
ZWEXPORT ZWError zway_cc_switch_color_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId, ZWBYTE state, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor SetMultiple
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: length
// Size of capabilities/states arrays (up to 16)
//
// @param: capabilityIds
// Array of capabilities to set
//
// @param: states
// Array of state values to be set for the capabilities
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01...0x7f in seconds
//  0x80...0xfe in minutes mapped to 1...127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: affected capabilityId subtrees updated
//
ZWEXPORT ZWError zway_cc_switch_color_set_multiple(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE length, const ZWBYTE * capabilityIds, const ZWBYTE * states, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor StartStateChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id to start changing state for
//
// @param: dir
// Direction of change: 0 to incrase, 1 to decrase
//
// @param: ignoreStartLevel
// @default: TRUE
// If set to True, device will ignore start level value and will use it's curent value
//
// @param: startLevel
// @default: 50
// Start level to change from
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: capabilityId subtree updated
//
ZWEXPORT ZWError zway_cc_switch_color_start_state_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId, ZWBYTE dir, ZWBOOL ignoreStartLevel, ZWBYTE startLevel, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor StopStateChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id to stop changing state for
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: capabilityId subtree updated
//
ZWEXPORT ZWError zway_cc_switch_color_stop_state_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId,  ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class BarrierOperator (0x66/102) //
// V1 C //
// Allows to control barriers and garage doors as well as their signal lamps
//
// @DH	state				Barrier state
// @DH	signalMask			Internal. Bit mask of available signals
// @DH	[signalId]			Subtree for signal
// @DH		signalTypeString	Signal description
// @DH		state			Signal state

// Send BarrierOperator Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: state updated
//
ZWEXPORT ZWError zway_cc_barrier_operator_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send BarrierOperator Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: state
// State to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: state updated
//
ZWEXPORT ZWError zway_cc_barrier_operator_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE state, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send BarrierOperator Signal Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: signalType
// Signal subsystem type to get state for
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: signalId subtree updated
//
ZWEXPORT ZWError zway_cc_barrier_operator_signal_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE signalType, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send BarrierOperator Signal Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: signalType
// Signal subsystem type to set state for
//
// @param: state
// State to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// @reported: signalId subtree updated
//
ZWEXPORT ZWError zway_cc_barrier_operator_signal_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE signalType, ZWBYTE state, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SimpleAVControl (0x94/148) //
// V4 S+C //
// Allows to control A/V devices
//
// @DH	bitmask			Bit mask with supported keys. Refer to Expert UI pyzw_zwave.js or Sigma Designs documentation for description of buttons.
// @DH	bitmasks		Internal
// @DH	sequenceNumber		Internal
// @DH	reportsNumber		Internal

// Send SimpleAVControl Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: keyAttribute
// 0 for key Down, 1 for key Up, 2 for key Alive (repeated every 100...200 ms)
//
// @param: avCommand
// Command to be sent. One of 465 predefined in Z-Wave protocol
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_simple_av_control_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE keyAttribute, unsigned int avCommand, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Security (0x98/152) //
// V1 S+C //
// This Command Class is transparently implemented in the library. There are no functions to execute.
//
// @DH	controller->data->secureControllerId	Node Id of secure controller: node that established secure channel when we are secondary controller (this data is on controller data tree)
// @DH	device->data->secureChannelEstablished	Flag describing if security interview was successful and secure channel is established (this data is on device data tree)
// @DH	secureNodeInfoFrame			Secure Node Information Frame
// @DH	securityAbandoned			Security interview failed
// @DH	scheme					Secure scheme supported
// @DH	securityRequested			Internal
// @DH	rNonce					Internal
// @DH	rNonceAckWait				Internal
// @DH	canStream				Internal
// @DH	firstPart				Internal
// @DH	sequenceId				Internal
// @DH	toFollow				Internal

// Send Security Inject
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: length
// Length of data
//
// @param: data
// Data to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_security_inject(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE length, const ZWBYTE *data, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class SecurityS2 (0x9f/159) //
// V1 S+C //
// This Command Class is transparently implemented in the library. There are no functions to execute.
//
// @DH	ctrlDevice->data->secureControllerId	Node Id of secure controller: node that established secure channel when we are secondary controller (this data is on controller data tree)
// @DH	device->data->secureChannelEstablished	Flag describing if security interview was successful and secure channel is established (this data is on device data tree)
// @DH	secureNodeInfoFrames			Secure Node Information Frames for each security level
// @DH	securityAbandoned			Security interview failed
// @DH	securityRequested			Internal
// @DH	requestedKeys				Subtree of requested keys
// @DH		S0				True if requested
// @DH		S2Unauthenticated		True if requested
// @DH		S2Authenticated			True if requested
// @DH		S2Access			True if requested
// @DH	grantedKeys				Subtree of granted keys
// @DH		S0				True if granted
// @DH		S2Unauthenticated		True if granted
// @DH		S2Authenticated			True if granted
// @DH		S2Access			True if granted
// @DH	device->data->securityS2ExchangedKeys	Mask of granted keys (for re-interview)
// @DH	publicKey				Public key of the device
// @DH	publicKeyVerified			Verified public key of the device by the user
// @DH	publicKeyAuthenticationRequired		True if the user have to verify
// @DH	controller->data->S2RequireCSA		Require Client Side Authentication during joining network as secondary

// Send Security S2 Inject
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: length
// Length of data
//
// @param: data
// Data to set
//
// @param: keyClass
// Security S2 key class
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_security_s2_inject(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE length, const ZWBYTE *data, ZWBYTE keyClass, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class CRC16 (0x56/86) //
// V1 S+C //
// This Command Class is transparently implemented in the library to use better 16 bits packet checksum. There are no functions to execute.
//
// @DH	crc16Requested		Internal


// Command Class MultiCmd (0x8F/143) //
// V1 S+C //
// This Command Class is transparently implemented in the library to save battery life time. There are no functions to execute.
//
// @DH	maxNum			Max number of packets to be encapsulated. Can be tunned to lower (to workaround buggy devices, 1 to turn off) or rise (to get bettery performance)


// Command Class Supervision (0x6C/108) //
// V1 S+C //
// This Command Class is transparently implemented in the library to guarantee delivery report on every command (even on Set). There are no functions to execute.
//
// @DH	[sessionId]			Subtree with session status
// @DH		status			Current session status (0 = Not supported, 1 = Working, 2 = Fail, 3 = Busy, 255 = Success)
// @DH		duration		Expected time to finish the operation
// @DH		moreStatusUpdates	True if more updates on the session status are expected
// @DH	lastSession			Internal


// Command Class Application Status (0x22/34) //
// V1 S+C //
// This Command Class is transparently implemented in the library to retry on device Busy report. There are no functions to execute.


// Command Class Version (0x86/134) //
// V2 S+C //
// Allows to get version of each Command Class supported by the device as well as firmware version.
//
// @DH	commandClass->data->version	Version of specific Command Class (this data is on Command Class data tree)
// @DH	ZWLib				SDK library type
// @DH	ZWProtocolMajor			SDK version major
// @DH	ZWProtocolMinor			SDK version minor
// @DH	SDK				SDK description
// @DH	applicationMajor		Application version major
// @DH	applicationMinor		Application version minor
// @DH	hardwareVersion			Hardware revision of the device
// @DH	firmwareCount			Number of chips (firmwares) in the device (excluding Z-Wave chip)
// @DH	[firmwareId]			Subtree for firmwareId information
// @DH		major			Additional chip application version major
// @DH		minor			Additional chip application version major


// Command Class DeviceResetLocally (0x5A/90) //
// V1 S+C //
// Reports to the controller that device was resetted locally (using local button operation)
//
// @DH	reset		Becomes True if the device sent us DeviceResetLocally notification. This means the device is certainly not in our network anymore


// Command Class Central Scene (0x5B/91) //
// V3 S+C //
// Allows to receive central controller oriented scene actions.
// Scenes are triggered by pushing a button on a remote control or wall controller.
// Note that Z-Way supports only V1, but in most cases you don't need it to be enabled in the NIF.
// Controlled version is V3.
//
// @DH	maxScenes			Number of scenes supported
// @DH	slowRefreshSupport		Flag to indicate if the device supports Slow Refresh mode
// @DH	slowRefresh			Flag to indicate if the device is currently in Slow Refresh mode
// @DH	currentScene			Last activated scene
// @DH	keyAttribute			Button (or key) action: 0 for key press, 1 for key release, 2 for key held down (should bre repeated at least every 200ms)
// @DH	sequence			Internal. To ignore duplicate packats.
// @DH	sceneSupportedKeyAttributesMask	Holds the list of supported key attributes for each scene
// @DH		[sceneId]		Array of supported key attributes for Scene Id: 0 for 1 press, 1 for release after hold, 2 for hold, 3..6 for 2..5 presses


/* Not implemented yet
 * // Command Class Schedule (0x53/83) //
 * // V1 C //
 * // Allows to exchange schedules which specify when to set a new behaviour.
 * // The Schedule Command Class is a generic scheduling Command Class that can be used to make schedules for any device type.
 * // @DH	[slotId]			...
 * // @DH		day			...
 * // @DH		month			...
 * // @DH		year			...
 * // @DH		weekday			...
 * // @DH		time			...
 * // @DH		duration		...
 * // @DH	max				...
 * // @DH	supportsDisable			...
 * // @DH	supportsFallback		...
 * // @DH	supportsOverride		...
 * // @DH	supportedStartTime		...
 * // @DH	supportedOverrideTypes		...
 * // @DH	supportedCommandClasses		...
 */


#endif
