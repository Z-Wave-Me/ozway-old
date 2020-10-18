#ifndef _Wrapper_H
#define _Wrapper_H

#include "Manager.h"

#include <ZWayLib.h>
#include <ZLogging.h>
#include <ZDataExt.h>

#define _NOT_YET_IMPLEMENTED_ zlog_write(Manager::Get()->m_logger, ZSTR("zway_debug"), Critical, "The method \"%s\" is not yet implemented, in %s, line %d\n", __func__,  __FILE__, __LINE__);
#define _NOT_SUPPORTED_ zlog_write(Manager::Get()->m_logger, ZSTR("zway_debug"), Critical, "The method \"%s\" is not supported, in %s, line %d\n", __func__,  __FILE__, __LINE__);

class Wrapper
{
	friend class Manager;
//	friend class Driver;
//	friend class Internal::CC::CommandClass;
//	friend class Group;
//	friend class Node;
//	friend class Internal::VC::Value;
//	friend class Internal::VC::ValueStore;
//	friend class Internal::Msg;

//private:
public:
	static void z_switch_binary_watcher(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg);
	static void z_watcher(const ZWay zway, ZWDeviceChangeType type, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE command_id, void *arg);
};

#endif
