#include "Wrapper.h"

#include "Manager.h"
#include "Defs.h"
#include "CompatOptionManager.h"
#include "Manager.h"
#include "Driver.h"
#include "Localization.h"
#include "Node.h"
#include "Notification.h"
#include "NotificationCCTypes.h"
#include "Options.h"
#include "Scene.h"
#include "SensorMultiLevelCCTypes.h"
#include "Utils.h"

#include "platform/Mutex.h"
#include "platform/Event.h"
#include "platform/Log.h"

#include "command_classes/CommandClasses.h"
#include "command_classes/CommandClass.h"
#include "command_classes/WakeUp.h"

#include "value_classes/ValueID.h"
#include "value_classes/ValueBool.h"
#include "value_classes/ValueButton.h"
#include "value_classes/ValueByte.h"
#include "value_classes/ValueDecimal.h"
#include "value_classes/ValueInt.h"
#include "value_classes/ValueList.h"
#include "value_classes/ValueRaw.h"
#include "value_classes/ValueSchedule.h"
#include "value_classes/ValueShort.h"
#include "value_classes/ValueString.h"
#include "value_classes/ValueBitSet.h"

#include <ZWayLib.h>
#include <ZLogging.h>
#include <ZDataExt.h>

using namespace OpenZWave;

void Wrapper::z_switch_binary_watcher(const ZDataRootObject root, ZWDataChangeType type, ZDataHolder data, void *arg)
{
	Notification *notification;
//	SwitchBinaryArg swBinArg = *(SwitchBinaryArg *)arg;
	ValueID valueId = *(ValueID *)arg;

	printf(">>>SwBinData %x\n", type);
	switch(type)
	{
		case Updated:
		{
			notification = new Notification(Notification::Type_ValueChanged);
//			notification->SetHomeAndNodeIds(swBinArg.home_id, swBinArg.node_id);
			notification->SetValueId(valueId);
			for (list<Watcher*>::iterator it = Manager::Get()->m_watchers.begin(); it != Manager::Get()->m_watchers.end(); ++it)
				(*it)->m_callback(notification, (*it)->m_context);
//			QueueNotification(notification);
			break;
		}
		case PhantomUpdate | Updated:
		{
			notification = new Notification(Notification::Type_ValueRefreshed);
//			notification->SetHomeAndNodeIds(swBinArg.home_id, swBinArg.node_id);
			notification->SetValueId(valueId);
			for (list<Watcher*>::iterator it = Manager::Get()->m_watchers.begin(); it != Manager::Get()->m_watchers.end(); ++it)
				(*it)->m_callback(notification, (*it)->m_context);
//			QueueNotification(notification);
			break;
		}
		case Invalidated:
		{
			break;
		}
		case Deleted:
		{
			break;
		}
		case ChildCreated:
		{
			break;
		}
		case ChildEvent:
		{
			break;
		}
	}
	printf("value_get\n");
}

void Wrapper::z_watcher(const ZWay zway, ZWDeviceChangeType type, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE command_id, void *arg)
{
//	Manager::Get()->m_notificationMutex->Lock();
	Notification *notification;
	uint32 home_id;
	
	printf("\n| Z-WATCHER: type: %x, nodeId: %d, instanceId: %d, commandId: %x\n\n", type, node_id, instance_id, command_id);

	zdata_acquire_lock(ZDataRoot(zway));
	zdata_get_integer(zway_find_controller_data(zway, "homeId"), (int *)&home_id);
	zdata_release_lock(ZDataRoot(zway));
	if (type & EnumerateExisting)
		printf("EnumerateExisting\n\t");
	switch (type & (~EnumerateExisting)) // TODO QueueNotification()
	{
		case DeviceAdded:
		{
			printf("DeviceAdded\n");
			notification = new Notification(Notification::Type_NodeAdded);
			notification->SetHomeAndNodeIds(home_id, node_id);
			for (list<Watcher*>::iterator it = Manager::Get()->m_watchers.begin(); it != Manager::Get()->m_watchers.end(); ++it)
				(*it)->m_callback(notification, (*it)->m_context);
//			QueueNotification(notification);
			break;
		}
		case DeviceRemoved:
		{
			printf("DeviceRemoved\n");
			notification = new Notification(Notification::Type_NodeRemoved);
			notification->SetHomeAndNodeIds(home_id, node_id);
			for (list<Watcher*>::iterator it = Manager::Get()->m_watchers.begin(); it != Manager::Get()->m_watchers.end(); ++it)
				(*it)->m_callback(notification, (*it)->m_context);
//			QueueNotification(notification);
			break;
		}
//TODO implement InstanceAdded & InstanceRemoved
		case InstanceAdded:
		{
			printf("InstanceAdded\n");
			break;
		}
		case InstanceRemoved:
		{
			printf("InstanceRemoved\n");
			break;
		}
		case CommandAdded:
		{
			printf("CommandAdded: %#2x\n", command_id);
			switch (command_id)
			{
//ZWEXPORT ZWError zdata_add_callback(ZDataHolder data, ZDataChangeCallback callback, ZWBOOL watch_children, void *arg);
				case 0x25:
				{
					printf("abcde\n");
					notification = new Notification(Notification::Type_ValueAdded);
//ValueID(uint32 const _homeId, uint8 const _nodeId, ValueGenre const _genre, uint8 const _commandClassId, uint8 const _instance, uint16 const _valueIndex, ValueType const _type) :
					notification->SetValueId(ValueID(home_id, node_id, ValueID::ValueGenre_User, command_id, instance_id, ValueID_Index_SwitchBinary::Level, ValueID::ValueType_Bool)); //TODO fix genre & valueType
					for (list<Watcher*>::iterator it = Manager::Get()->m_watchers.begin(); it != Manager::Get()->m_watchers.end(); ++it)
						(*it)->m_callback(notification, (*it)->m_context);
//					QueueNotification(notification);
					zdata_add_callback(zway_find_device_instance_cc_data(zway, node_id, instance_id, 0x25, "level"), Wrapper::z_switch_binary_watcher, TRUE, new ValueID(home_id, node_id, ValueID::ValueGenre_User, command_id, instance_id, 0, ValueID::ValueType_Bool));
					break;
				}
			}
			break;
		}
		case CommandRemoved:// TODO
		{
			printf("CommandRemoved\n");
			break;
		}
		default:
		{
			break;
		}
	}
	// Manager::Get()->m_notificationMutex->Unlock();
}
