    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoDaemon.cpp
*** \brief GizmoDaemon class body
***
*****************************************
  *****************************************
    **/
    
/*
  
  Copyright (c) 2007, Tim Burrell
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at 

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and 
  limitations under the License. 
  
*/

#include "GizmoDaemon.hpp"
#include "GizmoDaemonDefs.hpp"
#include "../libGizmod/GizmodThread.hpp"
#include "../libGizmod/GizmodTimer.hpp"
#include "../libGizmod/GizmoEventATIX10.hpp"
#include "../libGizmod/GizmoEventCPUUsage.hpp"
#include "../libGizmod/GizmoEventLIRC.hpp"
#include "../libGizmod/GizmoEventPowermate.hpp"
#include "../libGizmod/GizmoEventSoundCard.hpp"
#include "../libGizmod/GizmoEventStandard.hpp"
#include "../libGizmod/GizmoEventSoundCard.hpp"
#include "../libGizmod/GizmoEventSoundVisualization.hpp"
#include "../libGizmod/GizmoEventWindowFocus.hpp"
#include "../libGizmod/GizmoATIX10.hpp"
#include "../libGizmod/GizmoLIRC.hpp"
#include "../libGizmod/GizmoPowermate.hpp"
#include "../libGizmod/GizmoStandard.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include "../libH/Util.hpp"
#include "../libH/UtilFile.hpp"
#include "../libH/SocketException.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/python.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/tokenizer.hpp>
#include <fcntl.h>
#include <pystate.h>

using namespace std;
using namespace boost;
using namespace boost::program_options;
using namespace boost::python;
using namespace boost::filesystem;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs / defines
///////////////////////////////////////

/** 
 * \def    CONFIG_FILE
 * \brief  The default path of the config file
 */
#define CONFIG_FILE		PACKAGE ".conf"

/** 
 * \def    SCRIPT_DIR
 * \brief  The default path of the config file
 */
#define SCRIPT_DIR		SYSCONFDIR "/gizmod/"

/** 
 * \def    HOME_SCRIPT_DIR
 * \brief  The default path of the users home script dir
 */
#define HOME_SCRIPT_DIR		"~/.gizmod/"

/** 
 * \def    CONFIG_FILE_PATH
 * \brief  The default full path of the config file
 */
#define CONFIG_FILE_PATH	HOME_SCRIPT_DIR PACKAGE ".conf"

/** 
 * \def    USER_SCRIPT_DIR
 * \brief  The default path of the modules.d dir
 */
#define USER_SCRIPT_DIR		"modules.d"

/** 
 * \def    SCRIPT_DISPATCHER
 * \brief  The path of the initial config script
 */
#define SCRIPT_DISPATCHER 	"GizmodDispatcher.py"

/** 
 * \def    SCRIPT_USER
 * \brief  The path of the user config script that gets run after SCRIPT_DISPATCH
 */
#define SCRIPT_USER		"GizmodUser.py"

/** 
 * \def    EVENT_NODE_DIR
 * \brief  Default path to the event nodes
 */
#define EVENT_NODE_DIR		"/dev/input"

/** 
 * \def    LIRC_DEV
 * \brief  Default path to the LIRC device node
 */
#define LIRC_DEV		"/dev/lircd"

/** 
 * \def    NO_GETTER
 * \brief  Used when adding properties to pythong classes without a getter
 */
#define NO_GETTER		python::object()

/** 
 * \def    DEFAULT_PORT
 * \brief  Default port to start the server on
 */
#define DEFAULT_PORT		30303

/** 
 * \def    DEFAULT_PORT_STR
 * \brief  Default port to start the server on
 */
#define DEFAULT_PORT_STR	"30303"

////////////////////////////////////////////////////////////////////////////
// C++ -> Python Exposures
///////////////////////////////////////

/**
 * \struct GizmodEventHandlerInterfaceWrap
 * \brief  Wrapper for GizmodEventHandlerInterface so Python can inherit the abstract class
 */
struct GizmodEventHandlerInterfaceWrap : public GizmodEventHandlerInterface {
	/// Default Constructor
	GizmodEventHandlerInterfaceWrap(PyObject * self_) : self(self_) {}

	bool		getInitialized() { return python::call_method<bool>(self, "getInitialized"); }
	void		initialize()	 { return python::call_method<void>(self, "initialize"); }
	void		onDeregisterDevice(GizmoATIX10 const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoLIRC const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoPowermate const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onDeregisterDevice(GizmoStandard const * Device) { return python::call_method<void>(self, "onDeregisterDevice", ptr(Device)); }
	void		onEvent(GizmoEventATIX10 const * Event, GizmoATIX10 const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventCPUUsage const * Event) { return python::call_method<void>(self, "onEvent", ptr(Event)); }
	void		onEvent(GizmoEventLIRC const * Event, GizmoLIRC const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventPowermate const * Event, GizmoPowermate const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventSoundCard const * Event) { return python::call_method<void>(self, "onEvent", ptr(Event)); }
	void		onEvent(GizmoEventSoundVisualization const * Event) { return python::call_method<void>(self, "onEvent", ptr(Event)); }
	void		onEvent(GizmoEventStandard const * Event, GizmoStandard const * Device) { return python::call_method<void>(self, "onEvent", ptr(Event), ptr(Device)); }
	void		onEvent(GizmoEventWindowFocus const * Event) { return python::call_method<void>(self, "onEvent", ptr(Event)); }
	GizmoClass	onQueryDeviceClass(DeviceInfo DeviceInformation) { return python::call_method<GizmoClass>(self, "onQueryDeviceClass", DeviceInformation); };
	void		onRegisterDevice(GizmoATIX10 const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoLIRC const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoPowermate const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }
	void		onRegisterDevice(GizmoStandard const * Device) { return python::call_method<void>(self, "onRegisterDevice", ptr(Device)); }

	PyObject * 	self;			///< Pointer to self
};

/**
 * \brief  Python module definition
 */
BOOST_PYTHON_MODULE(GizmoDaemon) {
	/////////////////////////////////////////////////////////////////////
	// Enum exports
	///////////////////////////////////////
	
	/// AlsaEventType enum export
	enum_<AlsaEventType>("AlsaEventType")
		.value("Error",			ALSAEVENT_ERROR)
		.value("SoundCardAttach", 	ALSAEVENT_SOUNDCARD_ATTACH)
		.value("SoundCardDetach",	ALSAEVENT_SOUNDCARD_DETACH)
		.value("MixerElementAttach",	ALSAEVENT_MIXERELEMENT_ATTACH)
		.value("MixerElementChange",	ALSAEVENT_MIXERELEMENT_CHANGE)
		.value("MixerElementDetach",	ALSAEVENT_MIXERELEMENT_DETACH)
		;
	
	/// GizmoClass enum export
	enum_<GizmoClass>("GizmoClass")
		.value("ATIX10",		GIZMO_CLASS_ATIX10)
		.value("LIRC",	 		GIZMO_CLASS_LIRC)
		.value("Powermate", 		GIZMO_CLASS_POWERMATE)
		.value("Standard", 		GIZMO_CLASS_STANDARD)
		;
	
	/// GizmoEventClass enum export
	enum_<GizmoEventClass>("GizmoEventClass")
		.value("ATIX10", 		GIZMO_EVENTCLASS_ATIX10)
		.value("CPUUsage",		GIZMO_EVENTCLASS_CPUUSAGE)
		.value("LIRC",	 		GIZMO_EVENTCLASS_LIRC)
		.value("Powermate", 		GIZMO_EVENTCLASS_POWERMATE)
		.value("SoundCard",		GIZMO_EVENTCLASS_SOUNDCARD)
		.value("SoundVisualization",	GIZMO_EVENTCLASS_SOUNDVISUALIZATION)
		.value("Standard", 		GIZMO_EVENTCLASS_STANDARD)
		.value("WindowFocus",		GIZMO_EVENTCLASS_WINDOWFOCUS)
		;	
	
	/// SoundVisualizationEventType enum export
	enum_<SoundVisualizationEventType>("SoundVisualizationEventType")
		.value("Connect",		SOUNDVISUALIZATION_CONNECT)
		.value("Disconnect", 		SOUNDVISUALIZATION_DISCONNECT)
		.value("Render",		SOUNDVISUALIZATION_RENDER)
		;
	
	/// X11FocusEventType enum export
	enum_<X11FocusEventType>("X11FocusEventType")
		.value("FocusIn", 		X11FOCUSEVENT_IN)
		.value("FocusOut", 		X11FOCUSEVENT_OUT)
		;
	
	/// GizmoEventType and GizmoKey Python Enum Exposures
	#include "GizmoKeyDefPythonExposures.hpp"	
	
	/////////////////////////////////////////////////////////////////////
	// General Class exports
	///////////////////////////////////////
				 	
	/// AlsaInterface Python Class Export
	class_<AlsaInterface>("AlsaInterface")
		;
		 
	/// AlsaMixerElements Python Class Export
	class_<AlsaMixerElements>("AlsaMixerElements")
		.def_readonly("IsActive", &AlsaMixerElements::IsActive)
		.def_readonly("HasCommonVolume", &AlsaMixerElements::HasCommonVolume)
		.def_readonly("HasPlaybackVolume", &AlsaMixerElements::HasPlaybackVolume)
		.def_readonly("HasPlaybackVolumeJoined", &AlsaMixerElements::HasPlaybackVolumeJoined)
		.def_readonly("HasCaptureVolume", &AlsaMixerElements::HasCaptureVolume)
		.def_readonly("HasCaptureVolumeJoined", &AlsaMixerElements::HasCaptureVolumeJoined)
		.def_readonly("HasCommonSwitch", &AlsaMixerElements::HasCommonSwitch)
		.def_readonly("HasPlaybackSwitch", &AlsaMixerElements::HasPlaybackSwitch)
		.def_readonly("HasPlaybackSwitchJoined", &AlsaMixerElements::HasPlaybackSwitchJoined)
		.def_readonly("HasCaptureSwitch", &AlsaMixerElements::HasCaptureSwitch)
		.def_readonly("HasCaptureSwitchJoined", &AlsaMixerElements::HasCaptureSwitchJoined)
		.def_readonly("HasCaptureSwitchExclusive", &AlsaMixerElements::HasCaptureSwitchExclusive)
		.def_readonly("VolumeCapture", &AlsaMixerElements::VolumeCapture)
		.def_readonly("VolumeCaptureMin", &AlsaMixerElements::VolumeCaptureMin)
		.def_readonly("VolumeCaptureMax", &AlsaMixerElements::VolumeCaptureMax)
		.def_readonly("VolumeCapturePercent", &AlsaMixerElements::VolumeCapturePercent)	
		.def_readonly("VolumePlayback", &AlsaMixerElements::VolumePlayback)
		.def_readonly("VolumePlaybackMin", &AlsaMixerElements::VolumePlaybackMin)
		.def_readonly("VolumePlaybackMax", &AlsaMixerElements::VolumePlaybackMax)
		.def_readonly("VolumePlaybackPercent", &AlsaMixerElements::VolumePlaybackPercent)	
		.def_readonly("SwitchPlayback", &AlsaMixerElements::SwitchPlayback)
		.def_readonly("SwitchCapture", &AlsaMixerElements::SwitchCapture)
		;
		 
	/// AlsaMixer Python Class Export
	class_< AlsaMixer, bases<AlsaMixerElements> >("AlsaMixer")
		.def("getName", &AlsaMixer::getName)
		.add_property("Name", &AlsaMixer::getName)
		.def("getNameShort", &AlsaMixer::getNameShort)
		.add_property("NameShort", &AlsaMixer::getNameShort)
		.def("setSwitchCapture", &AlsaMixer::setSwitchCapture)
		.add_property("SwitchCapture", &AlsaMixer::SwitchCapture, &AlsaMixer::setSwitchCapture)
		.def("setSwitchPlayback", &AlsaMixer::setSwitchPlayback)
		.add_property("SwitchPlayback", &AlsaMixer::SwitchPlayback, &AlsaMixer::setSwitchPlayback)
		.def("setVolumeCapture", &AlsaMixer::setVolumeCapture)
		.add_property("VolumeCapture", &AlsaMixer::VolumeCapture, &AlsaMixer::setVolumeCapture)
		.def("setVolumeCapturePercent", &AlsaMixer::setVolumeCapturePercent)
		.add_property("VolumeCapturePercent", &AlsaMixer::VolumeCapturePercent, &AlsaMixer::setVolumeCapturePercent)
		.def("setVolumePlayback", &AlsaMixer::setVolumePlayback)
		.add_property("VolumePlayback", &AlsaMixer::VolumePlayback, &AlsaMixer::setVolumePlayback)
		.def("setVolumePlaybackPercent", &AlsaMixer::setVolumePlaybackPercent)
		.add_property("VolumePlaybackPercent", &AlsaMixer::VolumePlaybackPercent, &AlsaMixer::setVolumePlaybackPercent)
		;
		 
	/// AlsaSoundCard Python Class Export
	class_<AlsaSoundCard>("AlsaSoundCard", init<AlsaInterface *, int>())
		.def("getCardHardwareID", &AlsaSoundCard::getCardHardwareID)
		.add_property("CardHardwareID", &AlsaSoundCard::getCardHardwareID)
		.def("getCardID", &AlsaSoundCard::getCardID)
		.add_property("CardID", &AlsaSoundCard::getCardID)
		.def("getCardNameLong", &AlsaSoundCard::getCardNameLong)
		.add_property("CardNameLong", &AlsaSoundCard::getCardNameLong)
		.def("getCardName", &AlsaSoundCard::getCardName)
		.add_property("CardName", &AlsaSoundCard::getCardName)		
		.def("getMixer", &AlsaSoundCard::getMixer, return_internal_reference<>())
		.def("getNumMixers", &AlsaSoundCard::getNumMixers)
		.def("setAllPlaybackSwitches", &AlsaSoundCard::setAllPlaybackSwitches)
		;
	
	/// Alsa Python Class Export
	class_<Alsa>("Alsa")
		.def("getDefaultMixerSwitch", &Alsa::getDefaultMixerSwitch, return_internal_reference<>())			
		.add_property("DefaultMixerSwitch", make_function(&Alsa::getDefaultMixerSwitch, return_internal_reference<>()))
		.def("getDefaultMixerVolume", &Alsa::getDefaultMixerVolume, return_internal_reference<>())
		.add_property("DefaultMixerVolume", make_function(&Alsa::getDefaultMixerVolume, return_internal_reference<>()))
		.def("getSoundCard", &Alsa::getSoundCard, return_internal_reference<>())
		.def("getNumSoundCards", &Alsa::getNumSoundCards)
		.def("registerDefaultMixerPriority", &Alsa::registerDefaultMixerPriority)
		.def("toggleMuteAllCards", &Alsa::toggleMuteAllCards)
		;
				 
	/// DeviceInfo Python Class Export
	class_<DeviceInfo>("GizmoDeviceInfo")
		.def_readonly("DeviceName", &DeviceInfo::DeviceName)
		.def_readonly("DeviceIDBusType", &DeviceInfo::DeviceIDBusType)
		.def_readonly("DeviceIDVendor", &DeviceInfo::DeviceIDVendor)
		.def_readonly("DeviceIDProduct", &DeviceInfo::DeviceIDProduct)
		.def_readonly("DeviceIDVersion", &DeviceInfo::DeviceIDVersion)
		.def_readonly("FileName", &DeviceInfo::FileName)
		;
	
	/// Gizmo Python Class Export
	class_< Gizmo, bases<DeviceInfo> >("Gizmo", init<GizmoClass, const DeviceInfo &, int, int>())
		.def("getClass", &Gizmo::getClass)
		.add_property("Class", &Gizmo::getClass)				
		.def("getDeviceID", &Gizmo::getDeviceID)
		.add_property("DeviceID", &Gizmo::getDeviceID)
		.def("getDeviceClassID", &Gizmo::getDeviceClassID)
		.add_property("DeviceClassID", &Gizmo::getDeviceClassID)
		.def("getKeyState", &Gizmo::getKeyState)
		.def("getType", &Gizmo::getType)
		.add_property("Type", &Gizmo::getType)
		.def("setKeyState", &Gizmo::setKeyState)
		;
			
	/// CPUUsage Python Class Export
	class_<CPUUsage>("CPUUsage")
		.def("getNumCPUs", &CPUUsage::getNumCPUs)
		.def("setTimeBetweenUpdates", &CPUUsage::setTimeBetweenUpdates)
		;			
	
	/// Processes Python Class Export
	class_<Processes>("Processes")
		.def("isProcessRunning", &Processes::isProcessRunning)
			.staticmethod("isProcessRunning")
		.def("setTimeBetweenUpdates", &Processes::setTimeBetweenUpdates)
			.staticmethod("setTimeBetweenUpdates")
		.def("updateProcessTree", &Processes::updateProcessTree)
			.staticmethod("updateProcessTree")
		;		
	
	/// X11FocusWatcher Python Class Export
	class_<X11FocusWatcher>("X11FocusWatcher")
		.def("isApplicationRunning", &X11FocusWatcher::isApplicationRunning)
		.def("setInputFocus", &X11FocusWatcher::setInputFocus)
		;		
	
	/// GizmoUtils Python Class Export
	class_<GizmoUtils>("GizmoUtils")
		.def("bitDifference", &GizmoUtils::bitDifference)
			.staticmethod("bitDifference")
		;		
	
	/// GizmoDaemon Python Class Export
	class_<GizmoDaemon, bases<Alsa, X11FocusWatcher, Processes, CPUUsage, GizmoUtils> >("PyGizmoDaemon")
		.def("checkVersion", &GizmoDaemon::checkVersion)
		.def("getCurrentFocus", &GizmoDaemon::getCurrentFocus)
		.add_property("CurrentFocus", &GizmoDaemon::getCurrentFocus)
		.def("getDebugEnabled", &GizmoDaemon::getDebugEnabled)
		.add_property("DebugEnabled", &GizmoDaemon::getDebugEnabled)
		.def("getNumGizmosByClass", &GizmoDaemon::getNumGizmosByClass)
		.def("getUseKeyboardLEDs", &GizmoDaemon::getUseKeyboardLEDs)
		.add_property("UseKeyboardLEDs", &GizmoDaemon::getUseKeyboardLEDs)
		.def("getUseRemoteControl", &GizmoDaemon::getUseRemoteControl)
		.add_property("UseRemoteControl", &GizmoDaemon::getUseRemoteControl)
		.def("getVersion", &GizmoDaemon::getVersion)
		.add_property("Version", &GizmoDaemon::getVersion)
		.def("printNiceScriptInit", &GizmoDaemon::printNiceScriptInit)
		.def("printNiceScriptRegister", &GizmoDaemon::printNiceScriptRegister)
		.def("signalShutdown", &GizmoDaemon::signalShutdown)
		;
			
	/// GizmoTimeVal Python Class Export
	class_<GizmoTimeVal>("GizmoTimeVal")
		.def_readonly("Seconds", &GizmoTimeVal::Seconds)
		.def_readonly("MicroSeconds", &GizmoTimeVal::MicroSeconds)
		;
		
	/////////////////////////////////////////////////////////////////////
	// Event class exports
	///////////////////////////////////////
	
	/// AlsaEvent Python Class Export
 	class_<AlsaEvent>("AlsaEvent")
		.def_readonly("Type", &AlsaEvent::Type)
		.def_readonly("Mask", &AlsaEvent::Mask)		
		.def_readonly("IsActiveChanged", &AlsaEvent::IsActiveChanged)
		.def_readonly("ElementsChanged", &AlsaEvent::ElementsChanged)
		.def_readonly("VolumePlaybackChanged", &AlsaEvent::VolumePlaybackChanged)
		.def_readonly("VolumeCaptureChanged", &AlsaEvent::VolumeCaptureChanged)
		.def_readonly("SwitchPlaybackChanged", &AlsaEvent::SwitchPlaybackChanged)
		.def_readonly("SwitchCaptureChanged", &AlsaEvent::SwitchCaptureChanged)
		;
	
	/// GizmodEventHandlerInterface Python Class Export	
	class_<GizmodEventHandlerInterface, GizmodEventHandlerInterfaceWrap, boost::noncopyable>("GizmodEventHandler")
		;
	
	/// GizmodThread Python Class Export
	class_<GizmodThread>("GizmodThread", init<boost::python::object>())
		.def("create", &GizmodThread::create)
		;	

	/// GizmodTimer Python Class Export
	class_<GizmodTimer>("GizmodTimer", init<float, boost::python::object>())
		.def(init<float, boost::python::object, boost::python::object>())
		.def(init<float, boost::python::object, int, boost::python::object>())
		.def("start", &GizmodTimer::start)
		.def("setUserData", &GizmodTimer::setUserData)
		.def("setTime", &GizmodTimer::setTime)
		.def("resetTimer", &GizmodTimer::resetTimer)
		.def("cancel", &GizmodTimer::cancel)
		;	
	
	/// GizmoEvent Python Class Export
 	class_<GizmoEvent>("GizmoEvent", init<GizmoEventClass, bool>())
		.def("getClass", &GizmoEvent::getClass)
		.add_property("Class", &GizmoEvent::getClass)
		.def("isRemote", &GizmoEvent::isRemote)
		.add_property("Remote", &GizmoEvent::isRemote)
		;
		
	/// GizmoEventCPU Python Class Export
	class_< GizmoEventCPUUsage, bases<GizmoEvent> >("GizmoEventCPUUsage")
		.def("getCPUUsage", &GizmoEventCPUUsage::getCPUUsage)		
		.def("getCPUUsageAvg", &GizmoEventCPUUsage::getCPUUsageAvg)
		.def("getNumCPUs", &GizmoEventCPUUsage::getNumCPUs)
		.add_property("NumCPUs", &GizmoEventCPUUsage::getNumCPUs)
		;
			
	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventLIRC, bases<GizmoEvent> >("GizmoEventLIRC")
		.def_readonly("Code", &GizmoEventLIRC::Code)
		.def_readonly("Repeat", &GizmoEventLIRC::Repeat)
		.def_readonly("Button", &GizmoEventLIRC::Button)
		.def_readonly("Remote", &GizmoEventLIRC::Remote)
		;
		
	/// GizmoLinuxInputDevice Python Class Export
	class_<GizmoLinuxInputDevice>("GizmoLinuxInputDevice", init<const DeviceInfo &>())
		.def("createEventRaw", &GizmoLinuxInputDevice::createEventRaw)
		.def("createEventPress", &GizmoLinuxInputDevice::createEventPress)
		.def("createEvent", &GizmoLinuxInputDevice::createEventPress)
		.def("createEventPressMod", &GizmoLinuxInputDevice::createEventPressMod)
		.def("createEventPress", &GizmoLinuxInputDevice::createEventPressMod)
		.def("createEvent", &GizmoLinuxInputDevice::createEventPressMod)
		.def("createEvents", &GizmoLinuxInputDevice::createEvents)
		.def("grabExclusiveAccess", &GizmoLinuxInputDevice::grabExclusiveAccess)
		.def("remapKey", &GizmoLinuxInputDevice::remapKey)
		.def("setMinimumTimeBetweenEvents", &GizmoLIRC::setMinimumTimeBetweenEvents)
		;
	
	/// GizmoLinuxInputEvent Python Class Export 
	class_<GizmoLinuxInputEvent>("GizmoLinuxInputEvent")
		.def_readonly("RawCode", &GizmoLinuxInputEvent::RawCode)
		.def_readonly("RawType", &GizmoLinuxInputEvent::RawType)
		.def_readonly("Value", &GizmoLinuxInputEvent::Value)
		.def_readonly("TimeStamp", &GizmoLinuxInputEvent::TimeStamp)
		.def_readonly("Code", &GizmoLinuxInputEvent::Code)
		.def_readonly("Type", &GizmoLinuxInputEvent::Type)
		;
	
	/// GizmoEventATIX10 Python Class Export
	class_< GizmoEventATIX10, bases<GizmoEvent, GizmoLinuxInputEvent> >("GizmoEventATIX10")
		;
	
	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventPowermate, bases<GizmoEvent, GizmoLinuxInputEvent> >("GizmoEventPowermate")
		.def_readonly("ClickTime", &GizmoEventPowermate::ClickTime)
		;

	/// GizmoEventPowermate Python Class Export
	class_< GizmoEventStandard, bases<GizmoEvent, GizmoLinuxInputEvent> >("GizmoEventStandard")
		;

	/// GizmoEventSoundCard Python Class Export
	class_< GizmoEventSoundCard, bases<AlsaEvent, GizmoEvent> >("GizmoEventSoundCard", init<AlsaEvent const &, AlsaSoundCard const &, AlsaMixer const &>())
		.def("getMixer", &GizmoEventSoundCard::getMixer, return_internal_reference<>())
		.add_property("Mixer", make_function(&GizmoEventSoundCard::getMixer, return_internal_reference<>()))
		.def("getSoundCard", &GizmoEventSoundCard::getSoundCard, return_internal_reference<>())
		.add_property("SoundCard", make_function(&GizmoEventSoundCard::getSoundCard, return_internal_reference<>()))
		;

	/// GizmoEventSoundVisualization Python Class Export
	class_< GizmoEventSoundVisualization, bases<GizmoEvent> >("GizmoEventSoundVisualization")
		.def("getVULeft", &GizmoEventSoundVisualization::getVULeft)
		.add_property("VULeft", &GizmoEventSoundVisualization::getVULeft)
		.def("getVURight", &GizmoEventSoundVisualization::getVURight)
		.add_property("VURight", &GizmoEventSoundVisualization::getVURight)
		.def("getVUCombined", &GizmoEventSoundVisualization::getVUCombined)
		.add_property("VUCombined", &GizmoEventSoundVisualization::getVUCombined)
		.def("getType", &GizmoEventSoundVisualization::getType)
		.add_property("Type", &GizmoEventSoundVisualization::getType)
		;
		
	/// X11FocusEvent Python Class Export
	class_<X11FocusEvent>("X11FocusEvent", init<X11FocusEvent const &>())
		.def_readonly("WindowEventType", &X11FocusEvent::EventType)
		.def_readonly("WindowClass", &X11FocusEvent::WindowClass)
		.def_readonly("WindowName", &X11FocusEvent::WindowName)
		.def_readonly("WindowNameFormal", &X11FocusEvent::WindowNameFormal)
		;
		
	/// GizmoEventWindowFocus Python Class Export
	class_< GizmoEventWindowFocus, bases<X11FocusEvent, GizmoEvent> >("GizmoEventWindowFocus", init<X11FocusEvent const &>())
		;
		
	/////////////////////////////////////////////////////////////////////
	// Device class exports
	///////////////////////////////////////
	
	/// GizmoATIX10 Python Class Export
	class_< GizmoATIX10, bases<Gizmo, GizmoLinuxInputDevice> >("GizmoATIX10", init<const DeviceInfo &, int, int>())
		;

	/// GizmoLIRC Python Class Export
	class_< GizmoLIRC, bases<Gizmo> >("GizmoLIRC", init<const DeviceInfo &, int, int>())
		.def("setDisableFirstRepeats", &GizmoLIRC::setDisableFirstRepeats)
		.def("setMinimumTimeBetweenEvents", &GizmoLIRC::setMinimumTimeBetweenEvents)
		;
	
	/// GizmoPowermate Python Class Export
	class_< GizmoPowermate, bases<Gizmo, GizmoLinuxInputDevice> >("GizmoPowermate", init<const DeviceInfo &, int, int>())
		.def("changeLEDState", &GizmoPowermate::changeLEDState)
		.def("getLED", &GizmoPowermate::getLED)
		.def("getLEDPercent", &GizmoPowermate::getLEDPercent)		
		.def("getLEDPulseAsleep", &GizmoPowermate::getLEDPulseAsleep)
		.def("getRotated", &GizmoPowermate::getRotated)
		.def("pulseLED", &GizmoPowermate::pulseLED)
		.def("setLED", &GizmoPowermate::setLED)
		.def("setLEDPercent", &GizmoPowermate::setLEDPercent)
		.def("setLEDPulseAsleep", &GizmoPowermate::setLEDPulseAsleep)
		.def("setRotateSensitivity", &GizmoPowermate::setRotateSensitivity)
		.add_property("LED", &GizmoPowermate::getLED, &GizmoPowermate::setLED)
		.add_property("LEDPercent", &GizmoPowermate::getLEDPercent, &GizmoPowermate::setLEDPercent)
		.add_property("LEDPulseAsleep", &GizmoPowermate::getLEDPulseAsleep, &GizmoPowermate::setLEDPulseAsleep)
		.add_property("Rotated", &GizmoPowermate::getRotated)
		.add_property("RotateSensitivity", &GizmoPowermate::setRotateSensitivity)
		;

	/// GizmoStandard Python Class Export
	class_< GizmoStandard, bases<Gizmo, GizmoLinuxInputDevice> >("GizmoStandard", init<const DeviceInfo &, int, int>())
		;
}

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief  Default Constructor
 */
GizmoDaemon::GizmoDaemon() {
	cout << getProps();
	
	setConfigDir();
	mClientHost = "";
	mClientPort = DEFAULT_PORT;
	mDisabledALSA = false;
	mDisabledCPUUsage = false;
	mDisabledX11 = false;
	mDisableShutdownMessage = false;
	mEventsDir = EVENT_NODE_DIR;
	mInitialized = false;
	mLircDev = LIRC_DEV;
	mLocalDisabled = false;
	mpPyDispatcher = NULL;
	mReloadConfig = false;
	mServerPort = DEFAULT_PORT;
	mServerEnabled = false;
	mShuttingDown = false;
	mUseKeyboardLEDs = false;
	mUseRemoteControl = false;
	mVersion = 0.0;
	setVersionInfo();
}

/**
 * \brief  Default Destructor
 */
GizmoDaemon::~GizmoDaemon() {
	if (!mDisableShutdownMessage)
		cout << "GizmoDaemon Shutting Down... ";
	mShuttingDown = true;	
					if (!mDisableShutdownMessage) cout << "|"; flush(cout);
	X11FocusWatcher::shutdown();	if (!mDisableShutdownMessage) cout << "\b/"; flush(cout);
	Alsa::shutdown();		if (!mDisableShutdownMessage) cout << "\b-"; flush(cout);
	CPUUsage::shutdown();		if (!mDisableShutdownMessage) cout << "\b\\"; flush(cout);
	SocketServer::shutdown();	if (!mDisableShutdownMessage) cout << "\b|"; flush(cout);
	Py_Finalize();
	Py_Initialize();
	if (!mDisableShutdownMessage) 
		cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b Down.                  " << endl << endl;
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  See if a script's version matches GizmoDaemon
 * \param  Version The script's version
 * \param  Strict If set, the versions need to exactly match otherwise the script's Version signifies a minimum version level that Gizmod needs to be
 * \return True if versions are okay
 */
bool GizmoDaemon::checkVersion(double Version, bool Strict) {
	double VersionDiff = fabs(Version - mVersion);
	if (Strict) {
		return VersionDiff < 0.1;
	} else {
		if (Version - 0.05 <= mVersion)
			return true;
		else
			return false;
	}
}

/**
 * \brief  Delete a Gizmo
 * \param  FileName The filename of the Gizmo to be deleted
 */
void GizmoDaemon::deleteGizmo(std::string FileName) {
	if (mShuttingDown)
		return;
	
	// remove from map
	if (!mGizmos.count(FileName)) {
		// not found -- unusual, but whatever
		cdbg << "Tried to delete non-existent Gizmo [" << FileName << "]" << endl;
		return; 
	}
		
	// get the Gizmo
	shared_ptr<Gizmo> pGizmo = mGizmos[FileName];
	
	// signal python script
	try {
		mutex::scoped_lock lock(mMutexScript);
		switch (pGizmo->getClass()) {
		case GIZMO_CLASS_ATIX10:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoATIX10 const *>(pGizmo.get()));
			break;
 		case GIZMO_CLASS_LIRC:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoLIRC const *>(pGizmo.get()));
			break;
		case GIZMO_CLASS_POWERMATE: 
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoPowermate const *>(pGizmo.get()));
			break; 
		case GIZMO_CLASS_STANDARD:
			mpPyDispatcher->onDeregisterDevice(static_cast<GizmoStandard const *>(pGizmo.get()));
			break;
		}		
	} catch (error_already_set) {
		PyErr_Print();
		throw H::Exception("Failed to call GizmodDispatcher.onEvent for deleteGizmo", __FILE__, __FUNCTION__, __LINE__);
	}
		
	// remove the gizmo
	mGizmos.erase(FileName);
	cdbg2 << "Deleted Gizmo [" << FileName << "]" << endl;
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  EventClass The class of object to deserialize
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessage(GizmoEventClass EventClass, std::string const & Message) {	
	switch (EventClass) {
	case GIZMO_EVENTCLASS_ATIX10:
		deserializeMessageATIX10(Message);
		break;
	case GIZMO_EVENTCLASS_CPUUSAGE:
		deserializeMessageCPUUsage(Message);
		break;
	case GIZMO_EVENTCLASS_LIRC:
		deserializeMessageLIRC(Message);
		break;
	case GIZMO_EVENTCLASS_POWERMATE:
		deserializeMessagePowermate(Message);
		break;
	case GIZMO_EVENTCLASS_SOUNDCARD:
		deserializeMessageSoundcard(Message);
		break;
	case GIZMO_EVENTCLASS_SOUNDVISUALIZATION:
		deserializeMessageSoundVisualization(Message);
		break;
	case GIZMO_EVENTCLASS_STANDARD:
		deserializeMessageStandard(Message);
		break;
	case GIZMO_EVENTCLASS_WINDOWFOCUS:
		deserializeMessageWindowFocus(Message);
		break;
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessageATIX10(std::string const & Message) {	
	// separate the two components of the message
	size_t SepPos = Message.find("|");
	if (SepPos == string::npos) {
		cdbg << "Could not deserialize LIRC message -- invalid format" << endl;
		return;
	}
	string MessageEvent = Message.substr(0, SepPos);
	string MessageDevice = Message.substr(SepPos + 1);

	// deserialize
	stringstream InStreamEvent(MessageEvent);
	archive::text_iarchive InArchiveEvent(InStreamEvent);
	GizmoEventATIX10 Event;
	InArchiveEvent >> Event;
	Event.setIsRemote(true);
	
	stringstream InStreamDevice(MessageDevice);
	archive::text_iarchive InArchiveDevice(InStreamDevice);
	GizmoATIX10 Gizmo;
	InArchiveDevice >> Gizmo;
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event, &Gizmo);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessageCPUUsage(std::string const & Message) {	
	// deserialize
	stringstream InStream(Message);
	archive::text_iarchive InArchive(InStream);
	GizmoEventCPUUsage Event;
	InArchive >> Event;
	Event.setIsRemote(true);
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessageLIRC(std::string const & Message) {	
	// separate the two components of the message
	size_t SepPos = Message.find("|");
	if (SepPos == string::npos) {
		cdbg << "Could not deserialize LIRC message -- invalid format" << endl;
		return;
	}
	string MessageEvent = Message.substr(0, SepPos);
	string MessageDevice = Message.substr(SepPos + 1);

	// deserialize
	stringstream InStreamEvent(MessageEvent);
	archive::text_iarchive InArchiveEvent(InStreamEvent);
	GizmoEventLIRC Event;
	InArchiveEvent >> Event;
	Event.setIsRemote(true);
	
	stringstream InStreamDevice(MessageDevice);
	archive::text_iarchive InArchiveDevice(InStreamDevice);
	GizmoLIRC Gizmo;
	InArchiveDevice >> Gizmo;
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event, &Gizmo);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessagePowermate(std::string const & Message) {	
	// separate the two components of the message
	size_t SepPos = Message.find("|");
	if (SepPos == string::npos) {
		cdbg << "Could not deserialize LIRC message -- invalid format" << endl;
		return;
	}
	string MessageEvent = Message.substr(0, SepPos);
	string MessageDevice = Message.substr(SepPos + 1);

	// deserialize
	stringstream InStreamEvent(MessageEvent);
	archive::text_iarchive InArchiveEvent(InStreamEvent);
	GizmoEventPowermate Event;
	InArchiveEvent >> Event;
	Event.setIsRemote(true);
	
	stringstream InStreamDevice(MessageDevice);
	archive::text_iarchive InArchiveDevice(InStreamDevice);
	GizmoPowermate Gizmo;
	InArchiveDevice >> Gizmo;
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event, &Gizmo);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessageSoundcard(std::string const & Message) {	
	// deserialize
	stringstream InStream(Message);
	archive::text_iarchive InArchive(InStream);
	GizmoEventSoundCard Event;
	InArchive >> Event;
	Event.setIsRemote(true);
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessageSoundVisualization(std::string const & Message) {	
	// deserialize
	stringstream InStream(Message);
	archive::text_iarchive InArchive(InStream);
	GizmoEventSoundVisualization Event;
	InArchive >> Event;
	Event.setIsRemote(true);
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessageStandard(std::string const & Message) {	
	// separate the two components of the message
	size_t SepPos = Message.find("|");
	if (SepPos == string::npos) {
		cdbg << "Could not deserialize LIRC message -- invalid format" << endl;
		return;
	}
	string MessageEvent = Message.substr(0, SepPos);
	string MessageDevice = Message.substr(SepPos + 1);

	// deserialize
	stringstream InStreamEvent(MessageEvent);
	archive::text_iarchive InArchiveEvent(InStreamEvent);
	GizmoEventStandard Event;
	InArchiveEvent >> Event;
	Event.setIsRemote(true);
	
	stringstream InStreamDevice(MessageDevice);
	archive::text_iarchive InArchiveDevice(InStreamDevice);
	GizmoStandard Gizmo;
	InArchiveDevice >> Gizmo;
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event, &Gizmo);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Deserialize a network message into event Objects
 * \param  Message The message to be deserialized
 */
void GizmoDaemon::deserializeMessageWindowFocus(std::string const & Message) {	
	// deserialize
	stringstream InStream(Message);
	archive::text_iarchive InArchive(InStream);
	GizmoEventWindowFocus Event;
	InArchive >> Event;
	Event.setIsRemote(true);
	
	// process the remote event		
	if (!mLocalDisabled) {
		try {
			mutex::scoped_lock lock(mMutexScript);
			mpPyDispatcher->onEvent(&Event);
		} catch (error_already_set) {
			PyErr_Print();
			cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
		}
	}
}

/**
 * \brief  Enter the main run loop
 */
void GizmoDaemon::enterLoop() {
	if (mShuttingDown)
		return;
	if (!mInitialized)
		throw H::Exception("You must initialize GizmoDaemon first!", __FILE__, __FUNCTION__, __LINE__);
	
	watchForFileEvents();
}

/**
 * \brief  Get currently focused window
 * \return The X11FocusEvent containing information about the currently focused window
 * 
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".CurrentFocus"
 */
X11FocusEvent GizmoDaemon::getCurrentFocus() {
	return mCurrentFocus;
}

/**
 * \brief  Return whether debug mode is enabled or not
 * \return True if enabled
 * 
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".DebugEnabled"
 */
bool GizmoDaemon::getDebugEnabled() {
	return Debug::getEnabled();
}

/**
 * \brief  Get the event handler / dispatcher
 * \return The dispatcher
 */
GizmodEventHandlerInterface * GizmoDaemon::getDispatcher() {
	return mpPyDispatcher;
}

/**
 * \brief  Get a Gizmo by its file name
 * \param  FileName The filename of the gizmo to find
 * \return The Gizmo (shared_ptr) or a NULL shared_ptr if not found
 */
boost::shared_ptr<Gizmo> GizmoDaemon::getGizmoByFileName(std::string FileName) {
	return mGizmos[FileName];
}

/**
 * \brief  Get the number of Gizmos of a particular class
 * \param  Class The desired class
 * \return The number of Gizmos
 */
int GizmoDaemon::getNumGizmosByClass(GizmoClass Class) {
	int Count = 0;
	for (map< string, shared_ptr<Gizmo> >::iterator iter = mGizmos.begin(); iter != mGizmos.end(); iter ++) {
		shared_ptr<Gizmo> pGizmo = iter->second;
		if ( (pGizmo.get() != NULL) && (pGizmo->getClass() == Class) )
			Count ++;
	}
	return Count;
}

/**
 * \brief  Get a Gizmo Class ID
 * \param  Class The desired class
 * \return The Class ID
 */
int GizmoDaemon::getGizmoClassID(GizmoClass Class) {
	vector<bool> IDs;
	int tot = getNumGizmosByClass(Class);
	IDs.resize(tot + 1, false);
	
	for (map< string, shared_ptr<Gizmo> >::iterator iter = mGizmos.begin(); iter != mGizmos.end(); iter ++) {
		shared_ptr<Gizmo> pGizmo = iter->second;
		if ( (pGizmo.get() != NULL) && (pGizmo->getClass() == Class) )
			IDs[pGizmo->getDeviceClassID()] = true;
	}
	
	for (size_t lp = 0; lp < IDs.size(); lp ++) {		
		if (!IDs[lp])
			return lp;
	}

	return tot;
}

/**
 * \brief  Get the program's propers
 */
string GizmoDaemon::getProps() {
	return "\nGizmoDaemon v" VERSION " -=- (c) 2007, Tim Burrell <tim.burrell@gmail.com>\n=---------=\n";
}

/**
 * \brief  Get whether or not to reload the config
 * \return True if yes
 */
bool GizmoDaemon::getReloadConfig() {
	return mReloadConfig;
}

/**
 * \brief  Get whether or not to visualize on the keyboard LEDs
 * \return True if yes
 */
bool GizmoDaemon::getUseKeyboardLEDs() {
	return mUseKeyboardLEDs;
}

/**
 * \brief  Get whether or not to load the remote control script
 * \return True if yes
 */
bool GizmoDaemon::getUseRemoteControl() {
	return mUseRemoteControl;
}

/**
 * \brief  Get all the directories inside the user script dir
 *
 * This is for modifying the import path so that users can 
 * create directories inside the user script dir of scripts
 * to be imported
 */
std::string GizmoDaemon::getUserScriptDirPaths() {
	string ret;
	string UserScriptDir = mConfigDir + USER_SCRIPT_DIR;
	cdbg1 << "Adding [" << UserScriptDir << "] to the System Path" << endl;
	path UserScriptPath(UserScriptDir);
	if (!filesystem::exists(UserScriptPath))
		throw H::Exception("User Script dir [" + UserScriptDir + "] does NOT exist or permissions are wrong!", __FILE__, __FUNCTION__, __LINE__);
		
	// now register the event nodes
	// get a file listing
	directory_iterator endItr;
	for (directory_iterator iter(UserScriptDir); iter != endItr; iter ++) {
		if (filesystem::is_directory(*iter))
			ret += "sys.path.insert(0, \"" + iter->string() + "\")\n";
	}
	
	return ret;
}

/**
 * \brief  Get the program's version information
 *
 * Note that this is also implemented in Python as a property so it can
 * be accessed as a variable by referencing ".Version"
 */
double GizmoDaemon::getVersion() {
	return mVersion;
}

/**
 * \brief Handle incoming ATIX10 events
 * \param pWatchee The Watchee that triggered the event
 * \param ReadBuffer The data that was waiting on the device
 */
void GizmoDaemon::handleFileEventReadATIX10(GizmoATIX10 & Gizmo, DynamicBuffer<char> const & ReadBuffer) {
	std::vector< boost::shared_ptr<GizmoEventATIX10> > EventVector;
	GizmoEventATIX10::buildEventsVectorFromBuffer(EventVector, ReadBuffer, Gizmo.getSendNullEvents());
	for (size_t lp = 0; lp < EventVector.size(); lp ++) {
		if (Gizmo.processEvent(EventVector[lp].get()))
			if (!mLocalDisabled) {
				try {
					mutex::scoped_lock lock(mMutexScript);
					mpPyDispatcher->onEvent(EventVector[lp].get(), &Gizmo);
				} catch (error_already_set) {
					PyErr_Print();
					cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
				}
			}
	
			// try to send the remote event
			try {
				sendEventATIX10(static_cast<GizmoEventATIX10 const &>(*EventVector[lp]), static_cast<GizmoATIX10 const &>(Gizmo));
			} catch (SocketException const & e) {
				cdbg << "Failed to send LIRC Message to Server -- " << e.getExceptionMessage() << endl;
			}
	}
}

/**
 * \brief Handle incoming LIRC events
 * \param pWatchee The Watchee that triggered the event
 * \param ReadBuffer The data that was waiting on the device
 */
void GizmoDaemon::handleFileEventReadLIRC(GizmoLIRC & Gizmo, DynamicBuffer<char> const & ReadBuffer) {
	std::vector< boost::shared_ptr<GizmoEventLIRC> > EventVector;
	GizmoEventLIRC::buildEventsVectorFromBuffer(EventVector, ReadBuffer);
	for (size_t lp = 0; lp < EventVector.size(); lp ++) {
		if (Gizmo.processEvent(EventVector[lp].get())) {
			// process the local event
			if (!mLocalDisabled) {
				try {
					mutex::scoped_lock lock(mMutexScript);
					mpPyDispatcher->onEvent(EventVector[lp].get(), &Gizmo);
				} catch (error_already_set) {
					PyErr_Print();
					cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
				}
			}
			
			// try to send the remote event
			try {
				sendEventLIRC(static_cast<GizmoEventLIRC const &>(*EventVector[lp]), static_cast<GizmoLIRC const &>(Gizmo));
			} catch (SocketException const & e) {
				cdbg << "Failed to send LIRC Message to Server -- " << e.getExceptionMessage() << endl;
			}
		}
	}
}

/**
 * \brief Handle incoming Powermate events
 * \param pWatchee The Watchee that triggered the event
 * \param ReadBuffer The data that was waiting on the device
 */
void GizmoDaemon::handleFileEventReadPowermate(GizmoPowermate & Gizmo, DynamicBuffer<char> const & ReadBuffer) {
	std::vector< boost::shared_ptr<GizmoEventPowermate> > EventVector;
	GizmoEventPowermate::buildEventsVectorFromBuffer(EventVector, ReadBuffer, Gizmo.getSendNullEvents());
	for (size_t lp = 0; lp < EventVector.size(); lp ++) {
		if (Gizmo.processEvent(EventVector[lp].get()))
			if (!mLocalDisabled) {
				try {
					mutex::scoped_lock lock(mMutexScript);
					mpPyDispatcher->onEvent(EventVector[lp].get(), &Gizmo);
				} catch (error_already_set) {
					PyErr_Print();
					cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
				}
			}
	
			// try to send the remote event
			try {
				sendEventPowermate(static_cast<GizmoEventPowermate const &>(*EventVector[lp]), static_cast<GizmoPowermate const &>(Gizmo));
			} catch (SocketException const & e) {
				cdbg << "Failed to send LIRC Message to Server -- " << e.getExceptionMessage() << endl;
			}
	}
}

/**
 * \brief Handle incoming Standard events
 * \param pWatchee The Watchee that triggered the event
 * \param ReadBuffer The data that was waiting on the device
 */
void GizmoDaemon::handleFileEventReadStandard(GizmoStandard & Gizmo, DynamicBuffer<char> const & ReadBuffer) {
	std::vector< boost::shared_ptr<GizmoEventStandard> > EventVector;
	GizmoEventStandard::buildEventsVectorFromBuffer(EventVector, ReadBuffer, Gizmo.getSendNullEvents());
	for (size_t lp = 0; lp < EventVector.size(); lp ++) {
		if (Gizmo.processEvent(EventVector[lp].get()))
			if (!mLocalDisabled) {
				try {
					mutex::scoped_lock lock(mMutexScript);
					mpPyDispatcher->onEvent(EventVector[lp].get(), &Gizmo);
				} catch (error_already_set) {
					PyErr_Print();
					cerr << "Failed to call GizmodDispatcher.onEvent for deserializeMessage" << endl;
				}
			}
		
			// try to send the remote event
			try {
				sendEventStandard(static_cast<GizmoEventStandard const &>(*EventVector[lp]), static_cast<GizmoStandard const &>(Gizmo));
			} catch (SocketException const & e) {
				cdbg << "Failed to send LIRC Message to Server -- " << e.getExceptionMessage() << endl;
			}
	}
}

/**
 * \brief  Setup GizmoDaemon
 * 
 * Initialize GizmoDaemon
 */
void GizmoDaemon::initGizmod() {
	if (mInitialized)
		return;
	
	// initialize signals
	initSignals();
		
	// init python
	try {
		initPython();
		if (mShuttingDown)
			return;
	} catch (H::Exception & e) {
		throw e;
	} catch (exception & e) {
		throw H::Exception("Failed to Initialize Python!", __FILE__, __FUNCTION__, __LINE__);
	}
	
	// initialize the client
	if (mClientHost != "") {
		try {
			cout << "Connecting to [" << mClientHost << "] at Port [" << mClientPort << "]..." << endl;
			connectToServer(mClientHost, mClientPort);
			if (mShuttingDown)
				return;
		} catch (SocketException const & e) {
			throw H::Exception(e.getExceptionMessage(), __FILE__, __FUNCTION__, __LINE__);
		}
	}
	
	// register all the devices
	try {
		registerDevices();
		if (mShuttingDown)
			return;
	} catch (H::Exception & e) {
		throw e;
	}
	
	// load the user scripts
	try {
		loadUserScripts();
		if (mShuttingDown)
			return;
	} catch (H::Exception & e) {
		throw e;
	}
	
	// initialize the server
	if (mServerEnabled) {
		try {
			acceptConnections(mServerPort);
		} catch (SocketException const & e) {
			throw H::Exception("Failed to Start Server -- " + e.getExceptionMessage(), __FILE__, __FUNCTION__, __LINE__);
		}
	}
				
	// init the X11FocusWatcher
	if (!mDisabledX11)
		X11FocusWatcher::init();
	
	// init the CPU Usage watcher
	if (!mDisabledCPUUsage)
		CPUUsage::init();
	
	// init Alsa
	if (!mDisabledALSA) {
		try {
			Alsa::init();
		} catch (H::Exception & e) {
			cerr << e.getExceptionMessage() << endl;
		}
	}
		
	// success
	mInitialized = true;
}

/**
 * \brief  Initialize the Python interpreter
 */
void GizmoDaemon::initPython() {
	try {
		cdbg1 << "Embedding Python Interpreter..." << endl;
		PyImport_AppendInittab("GizmoDaemon", &initGizmoDaemon);
		
		// initialize python and threads
		Py_Initialize();
		
		cdbg1 << "Initializing Python Environment..." << endl;
		mPyMainModule = object((handle<>(borrowed(PyImport_AddModule("__main__")))));
		mPyMainNamespace = mPyMainModule.attr("__dict__");
		
		// add Gizmo Daemon module automatically to the namespace
		object GizmoDaemonModule( (handle<>(PyImport_ImportModule("GizmoDaemon"))) );
		mPyMainNamespace["GizmoDaemon"] = GizmoDaemonModule;
		
		// create a new object so the script can access this object
		scope(GizmoDaemonModule).attr("Gizmod") = ptr(this);
		
		// Modify the PYTHONPATH so import's work
		string PathInsertion = 
			"import sys\nsys.path.insert(0, \"" + mConfigDir + "\")\n" +
			"sys.path.insert(0, \"" + mConfigDir + USER_SCRIPT_DIR + "/\")\n" +
			getUserScriptDirPaths();
		cdbg1 << "Modifying PYTHONPATH:\n" << PathInsertion << endl;
		handle<> ignore_path_exec((PyRun_String(
			PathInsertion.c_str(),
			Py_file_input, mPyMainNamespace.ptr(), mPyMainNamespace.ptr())));
		
		// execute the main script code
		string ScriptFile = mConfigDir + SCRIPT_DISPATCHER;
		cdbg1 << "Executing Dispatcher Python Script [" << ScriptFile << "]..." << endl;
		FILE * ifScript = fopen(ScriptFile.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + ScriptFile + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, ScriptFile.c_str());
		fclose(ifScript);
		
		// Create the event dispatcher object so we can interact with it
		cdbg1 << "Creating Dispatcher Object" << endl;
		handle<> ignore_dispatcher_exec((PyRun_String(
			"Dispatcher = GizmodDispatcher()\nGizmod.Dispatcher = Dispatcher\n",
			Py_file_input, mPyMainNamespace.ptr(), mPyMainNamespace.ptr())));
		
		// Grab the event dispatcher object so we can interact with it
		mpPyDispatcher = extract<GizmodEventHandlerInterface*>(mPyMainNamespace["Dispatcher"]);
		
		// Initialize the dispatcher object
		mpPyDispatcher->initialize();
							
		// execute the user script code
		ScriptFile = mConfigDir + SCRIPT_USER;
		cdbg1 << "Executing User Python Script [" << ScriptFile << "]..." << endl;
		ifScript = fopen(ScriptFile.c_str(), "r");
		if (!ifScript)
			throw H::Exception("Failed to Open Python Script [" + ScriptFile + "] for Reading", __FILE__, __FUNCTION__, __LINE__);
		PyRun_SimpleFile(ifScript, ScriptFile.c_str());
		fclose(ifScript);
	} catch (error_already_set) {
		PyErr_Print();
		throw H::Exception("Failed to Execute Python Script!", __FILE__, __FUNCTION__, __LINE__);
	}
}

/**
 * \brief  generic Init stuff
 * \param  argc number of command line arguments
 * \param  argv command line arguments
 * \return true if the program should continue, false otherwise
 * 
 * load the config file, process command line options, etc
 */
bool GizmoDaemon::initialize(int argc, char ** argv) {
	// generic options
	options_description GenericOptions("Generic Options");
	GenericOptions.add_options()
		("debug,g",					"Enable debug mode")
		("help,h",					"Display informative help message")
		("verbosity,V",		value<int>(),		"Set debug vebosity level (0-5) [Default = 0]")
		("version,v",					"Print version information")
		;
				
	// config file options that can be loaded via command line as well
	options_description ConfigurationOptions("Configuration Options");
	ConfigurationOptions.add_options()
		("client-host,c",	value<string>(),	"Enable event forwarding to a remote host")
		("client-port,P",	value<int>(),		"Port to forward events to (default: " DEFAULT_PORT_STR ")")
		("config-dir,C",	value<string>(),	"Set config scripts directory") 
		("events-dir,e",	value<string>(),	"Set event node directory (default: " EVENT_NODE_DIR ")")
		("keyboard-leds,k",				"Allow Gizmod to Visualize on the Keyboard LEDs")
		("lirc-dev,l",		value<string>(),	"Set LIRC device node (default: " LIRC_DEV ")")
		("no-alsa,A",					"Disable ALSA support")
		("no-cpuusage,U",				"Disable CPU Usage reporting")
		("no-local,N",					"Disable local processing of events")
		("no-x11,X",					"Disable X11 support")
		("remote-control,r",				"Enable Remote Control mode")
		("server,s",					"Enable server (default: not enabled)")
		("server-port,p",	value<int>(),		"Port to start Gizmod server on (default: " DEFAULT_PORT_STR ")")
		;
        
        // hiGizmoDaemonn options
	options_description HiddenOptions("Hidden Options");
	HiddenOptions.add_options();
       
        // create command line options group
        options_description CommandLineOptions;
        CommandLineOptions.add(GenericOptions).add(ConfigurationOptions).add(HiddenOptions);

        // create config file options group
        options_description ConfigFileOptions;
        ConfigFileOptions.add(ConfigurationOptions).add(HiddenOptions);
	
	// create a visible options group for help display
	options_description VisibleOptions("");
	VisibleOptions.add(GenericOptions).add(ConfigurationOptions);
	
	// create the variables map
	variables_map VarMap;
	
	// try parsing the command line
	try {
		store(parse_command_line(argc, argv, CommandLineOptions), VarMap);
	} catch (exception & e) {
		cout << VisibleOptions;
		throw H::Exception("Invalid Command Line Argument(s)");
	}

	// try parsing the config file
	try {
		string ConfigFile = CONFIG_FILE_PATH;
		UtilFile::relativeToAbsolute(ConfigFile);
		ifstream ifs(ConfigFile.c_str());
		if (ifs.is_open())
			store(parse_config_file(ifs, ConfigFileOptions), VarMap);
	} catch (exception & e) {
		cout << VisibleOptions;
		throw H::Exception("Invalid Configuration File");
	}
	
	// build the option map
	notify(VarMap);

	// check for options
	if (VarMap.count("help")) {
		cout << VisibleOptions << endl;
		mDisableShutdownMessage = true;
		return false;
	}
	if (VarMap.count("version")) {
		cout << endl;
		mDisableShutdownMessage = true;
		return false;
	}
	if (VarMap.count("debug")) {
		Debug::setEnabled(true);	
		cdbg << "Debug Mode Enabled" << endl;
	}
	if (VarMap.count("verbosity")) {
		Debug::setVerbosity(VarMap["verbosity"].as<int>());
		cdbg << "Debug Verbosity set to [" << VarMap["verbosity"].as<int>() << "]" << endl;
	}
	if (VarMap.count("client-host")) {
		mClientHost = VarMap["client-host"].as<string>();
		cdbg << "Client Forwarding to [" << mClientHost << "]" << endl;
	}
	if (VarMap.count("client-port")) {
		mClientPort = VarMap["client-port"].as<int>();
		cdbg << "Client port set to [" << mClientPort << "]" << endl;
	}
	if (VarMap.count("config-dir")) {
		mConfigDir = VarMap["config-dir"].as<string>();
		if (mConfigDir[mConfigDir.length() - 1] != '/')
			mConfigDir += "/";
		cdbg << "Config Scripts Directory set to [" << mConfigDir << "]" << endl;
	}
	if (VarMap.count("events-dir")) {
		mEventsDir = VarMap["events-dir"].as<string>();
		if (mEventsDir[mEventsDir.length() - 1] != '/')
			mEventsDir += "/";
		cdbg << "Event Node Directory set to [" << mEventsDir << "]" << endl;
	}
	if (VarMap.count("keyboard-leds")) {
		cdbg << "Allowing takeover of Keyboard LEDs" << endl;
		mUseKeyboardLEDs = true;
	}	
	if (VarMap.count("lirc-dev")) {
		mLircDev = VarMap["lirc-dev"].as<string>();
		cdbg << "LIRC Device Node set to [" << mLircDev << "]" << endl;
	}
	if (VarMap.count("no-alsa")) {
		mDisabledALSA = true;
		cdbg << "ALSA Support Disabled" << endl;
	}
	if (VarMap.count("no-cpuusage")) {
		mDisabledCPUUsage = true;
		cdbg << "CPU Usage Reporting Disabled" << endl;
	}
	if (VarMap.count("no-local")) {
		mLocalDisabled = true;
		cdbg << "Local Event Processing Disabled" << endl;
	}
	if (VarMap.count("no-x11")) {
		mDisabledX11 = true;
		cdbg << "X11 Support Disabled" << endl;
	}
	if (VarMap.count("remote-control")) {
		mUseRemoteControl = true;
		cdbg << "Remote Control Mode Enabled" << endl;
	}
	if (VarMap.count("server")) {
		mServerEnabled = !mServerEnabled;
		cdbg << "Gizmod Server Enabled" << endl;
	}
	if (VarMap.count("server-port")) {
		mServerPort = VarMap["server-port"].as<int>();
		cdbg << "Sever port set to [" << mServerPort << "]" << endl;
	}

	cout << endl;
	return true;
}

/**
 * \brief Load user scripts
 */
void GizmoDaemon::loadUserScripts() {
	cout << "Loading User Scripts:" << endl << endl;
	
	path UserScriptPath(mConfigDir + USER_SCRIPT_DIR);
	if (!filesystem::exists(UserScriptPath))
		throw H::Exception("User script directory [" + mConfigDir + USER_SCRIPT_DIR + "] does NOT exist or permissions are wrong!", __FILE__, __FUNCTION__, __LINE__);
		
	// now register the event nodes
	// get a file listing
	std::vector<string> UserScripts;
	directory_iterator endItr;
	for (directory_iterator iter(mConfigDir + USER_SCRIPT_DIR); iter != endItr; iter ++) {
		if ( (!filesystem::is_directory(*iter)) && (!filesystem::symbolic_link_exists(*iter)) ) {
			UserScripts.push_back(iter->leaf());
		}
	}
	
	// sort the list of input event nodes
	sort_all(UserScripts);
	
	// load the user scripts (and lock the mutex)
	mutex::scoped_lock lock(mMutexScript);
	apply_func(UserScripts, &GizmoDaemon::loadUserScriptsFunctor, this);
	cout << endl;
}

/**
 * \brief Load user scripts functor
 * \param UserScript The user script to load
 */
void GizmoDaemon::loadUserScriptsFunctor(std::string UserScript) {
	// Note: Mutex is already locked!
	
	// make sure it's a python script, and remove extension
	size_t dotPos = UserScript.rfind(".py");
	if ( (dotPos == string::npos) || (dotPos != UserScript.length() - 3) )
		return;
	UserScript = UserScript.substr(0, dotPos);
	cdbg1 << "Importing User Script [" << UserScript << "]" << endl;
	
	// Import the module
	try {
		string ImportModuleString = "__import__(\"" + UserScript + "\")\n";
		cdbg2 << "Executing Python Code: " << ImportModuleString << endl;
		handle<> ignore_path_exec((PyRun_String(
			ImportModuleString.c_str(),
			Py_file_input, mPyMainNamespace.ptr(), mPyMainNamespace.ptr())));
	} catch (error_already_set) {
		PyErr_Print();
		throw H::Exception("Failed to Load User Script [" + UserScript + "]", __FILE__, __FUNCTION__, __LINE__);
	}
}

/**
 * \brief  Scripts can call this to print a nice looking init string
 * \param  Width Placement positions
 * \param  Text1 Text field 1
 * \param  Text2 Text field 2
 * \param  Text3 Text field 3
 */
void GizmoDaemon::printNiceScriptInit(int Width, std::string Text1, std::string Text2, std::string Text3) {
	replace_all(Text1, "\n", ""); 
	replace_all(Text2, "\n", ""); 
	replace_all(Text3, "\n", "");
	trim(Text1); 
	trim(Text2); 
	trim(Text3);
	switch (Width) {
	case 0:
		Width = 12;
		break;
	case 1:
		Width = 22;
		break;
	}
	int StartPos = Width - Text1.length();
	for (int lp = 0; lp < StartPos; lp ++)
		cout << " ";
	cout << Text1;
	if (Text2 != "")
		cout << " - " << Text2;
	if (Text3 != "")
		cout << " [" << Text3 << "]";
	cout << endl;
}

/**
 * \brief  Scripts can call this to print a nice looking register string
 * \param  Width Placement positions
 * \param  Text1 Text field 1
 * \param  Text2 Text field 2
 * \param  Text3 Text field 3
 * \param  Text4 Text field 4
 * \param  Text5 Text field 5
 */
void GizmoDaemon::printNiceScriptRegister(int Width, std::string Text1, std::string Text2, std::string Text3, std::string Text4, std::string Text5) {
	replace_all(Text1, "\n", ""); 
	replace_all(Text2, "\n", ""); 
	replace_all(Text3, "\n", "");
	replace_all(Text4, "\n", ""); 
	replace_all(Text5, "\n", "");
	trim(Text1); 
	trim(Text2); 
	trim(Text3);
	trim(Text4);
	trim(Text5);
	switch (Width) {
	case 0:
		Width = 12;
		break;
	case 1:
		Width = 22;
		break;
	}
	int StartPos = Width - Text1.length();
	for (int lp = 0; lp < StartPos; lp ++)
		cout << " ";
	cout << Text1;
	if (Text2 != "")
		cout << " - " << Text2;
	if (Text3 != "") {
		size_t lastSPos = Text3.rfind("/");
		if (lastSPos != string::npos)
			Text3 = Text3.substr(lastSPos + 1);
		cout << " [" << Text3 << "]";
	}
	if ( (Text4 != "") && (Text4 != "-0x1") && (Text4 != "0xffff") )
		cout << " vId: " << Text4;
	if ( (Text4 != "") && (Text5 != "-0x1") && (Text5 != "0xffff") )
		cout << " pId: " << Text5;
	cout << endl;
}

/**
 * \brief  Triggered when a mixer element is discovered
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 * \param  Mixer The mixer element that triggered the event
 */
void GizmoDaemon::onAlsaEventMixerElementAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer) {
	if (mShuttingDown)
		return;
	
	cdbg1 << "Mixer Element Attached [" << Mixer.getName() << "] on Sound Card [" << SoundCard.getCardName() << "]" << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventSoundCard EventSoundCard(Event, SoundCard, Mixer);
		
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&EventSoundCard);
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onAlsaEventMixerElementAttach" << endl;
	}
}

/**
 * \brief  Triggered when a mixer element is changed
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 * \param  Mixer The mixer element that triggered the event
 */
void GizmoDaemon::onAlsaEventMixerElementChange(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer) {
	if (mShuttingDown)
		return;
	
	if (Event.Type == ALSAEVENT_MIXERELEMENT_CHANGE) 
		cdbg2 << "Mixer Element Changed [" << Mixer.getName() << "] with Mask [" << Event.IsActiveChanged << Event.ElementsChanged << Event.VolumePlaybackChanged << "] on Sound Card [" << SoundCard.getCardName() << "] " << Mixer.VolumePlaybackPercent << endl;
	else
		cdbg2 << "Mixer Element Changed [" << Mixer.getName() << "] with Mask [" << Event.Mask << "] on Sound Card [" << SoundCard.getCardName() << "]" << endl;
	
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventSoundCard EventSoundCard(Event, SoundCard, Mixer);
		
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&EventSoundCard);
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onAlsaEventMixerElementChange" << endl;
	}
}

/**
 * \brief  Triggered when a mixer element is detached
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 * \param  Mixer The mixer element that triggered the event
 */
void GizmoDaemon::onAlsaEventMixerElementDetach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard, AlsaMixer const & Mixer) {
	if (mShuttingDown)
		return;
	
	cdbg3 << "Mixer Element Detached [" << Mixer.getName() << "] on Sound Card [" << SoundCard.getCardName() << "]" << endl;	
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventSoundCard EventSoundCard(Event, SoundCard, Mixer);
		
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&EventSoundCard);
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onAlsaEventMixerElementDetach" << endl;
	}
}

/**
 * \brief  Triggered when a new sound card is detected
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 */
void GizmoDaemon::onAlsaEventSoundCardAttach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard) {
	if (mShuttingDown)
		return;
	
	cdbg << "Attached to Sound Card [" << SoundCard.getCardHardwareID() << "] -- " << SoundCard.getCardName() << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventSoundCard EventSoundCard(Event, SoundCard);
		
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&EventSoundCard);
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onAlsaEventSoundCardAttach" << endl;
	}
}

/**
 * \brief  Triggered when a sound card is removed
 * \param  Event The event
 * \param  SoundCard The sound card that triggered the event
 */
void GizmoDaemon::onAlsaEventSoundCardDetach(AlsaEvent const & Event, AlsaSoundCard const & SoundCard) {
	if (mShuttingDown)
		return;
	
	cdbg1 << "Sound Card Detached [" << SoundCard.getCardHardwareID() << "] -- " << SoundCard.getCardName() << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventSoundCard EventSoundCard(Event, SoundCard);
		
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&EventSoundCard);
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onAlsaEventSoundCardDetach" << endl;
	}
}

/**
 * \brief  Event triggered when CPU Usage stats are updated
 * \param  Event A vector of CPU Usage info, where index 0 is ALL processors, 1 is proc 1, 2 is cpu 2, etc
 */
void GizmoDaemon::onCPUUsage(std::vector< boost::shared_ptr<CPUUsageInfo> > const & Event) {	
	if (mShuttingDown)
		return;
	
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventCPUUsage const EventCPUUsage(Event);
		
		// process the local event
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&EventCPUUsage);
		
		// process the remote event
		try {
			sendEventCPUUsage(Event);
		} catch (SocketException const & e) {
			cdbg << "Failed to send CPUUsage Message to Server -- " << e.getExceptionMessage() << endl;
		}		
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onCPUUsage" << endl; 
	}	
}

/**
 * \brief Event triggered when a new file is created
 * \param pWatchee The Watchee that triggered the event
 * \param FullPath The full (absolute) path of the new file
 * \param FileName The file name (relative ) of the new file
 */
void GizmoDaemon::onFileEventCreate(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName) {
	if (FileName.find("event") != 0) {
		cout << "onFileEventCreate [" << FullPath << "]" << endl;
		return;
	}
	addFileToWatch(FullPath, WATCH_INOUT);
}

/**
 * \brief Event triggered when a file is deleted
 * \param pWatchee The Watchee that triggered the event
 * \param FullPath The full (absolute) path of the new file
 * \param FileName The file name (relative ) of the new file
 */
void GizmoDaemon::onFileEventDelete(boost::shared_ptr<H::FileWatchee> pWatchee, std::string FullPath, std::string FileName) {
	cdbg5 << "onFileEventDelete [" << FullPath << "] -- " << pWatchee->FileName << endl;
	deleteGizmo(pWatchee->FileName);
}

/**
 * \brief Event triggered when a file is disconnected
 * \param pWatchee The Watchee that triggered the event
 */
void GizmoDaemon::onFileEventDisconnect(boost::shared_ptr<H::FileWatchee> pWatchee) {
	cdbg5 << "onFileEventDisconnect [" << pWatchee->FileName << "]: " << pWatchee->DeviceName << endl;
	deleteGizmo(pWatchee->FileName);
}

/**
 * \brief Event triggered when data is waiting on a device
 * \param pWatchee The Watchee that triggered the event
 * \param ReadBuffer The data that was waiting on the device
 */
void GizmoDaemon::onFileEventRead(boost::shared_ptr<H::FileWatchee> pWatchee, DynamicBuffer<char> const & ReadBuffer) {
	if (mShuttingDown)
		return;
	
	// make sure the gizmo exists
	shared_ptr<Gizmo> pUnknownGizmo = mGizmos[pWatchee->FileName];
	if (!pUnknownGizmo) {
		cdbg << "Unknown Event Detected on Device [" << pWatchee->DeviceName << "] of Length [" << (int) ReadBuffer.length() << "]" << endl;
		return;
	}
				
	// create the event and dispatch it
	try {
		switch (pUnknownGizmo->getClass()) {
		case GIZMO_CLASS_ATIX10:
			handleFileEventReadATIX10(static_cast<GizmoATIX10 &>(*pUnknownGizmo), ReadBuffer);
			break;
		case GIZMO_CLASS_LIRC:
			handleFileEventReadLIRC(static_cast<GizmoLIRC &>(*pUnknownGizmo), ReadBuffer);
			break;
		case GIZMO_CLASS_POWERMATE:
			handleFileEventReadPowermate(static_cast<GizmoPowermate &>(*pUnknownGizmo), ReadBuffer);
			break;			
		case GIZMO_CLASS_STANDARD: 
			handleFileEventReadStandard(static_cast<GizmoStandard &>(*pUnknownGizmo), ReadBuffer);
			break;			
		}
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onFileEventRead" << endl;
	}
}

/**
 * \brief Event triggered when a new device is registered
 * \param pWatchee The Watchee that triggered the event
 */
void GizmoDaemon::onFileEventRegister(boost::shared_ptr<H::FileWatchee> pWatchee) {
	if (mShuttingDown)
		return;
	
	cdbg1 << "New Device Detected [" << pWatchee->FileName << "]: " << pWatchee->DeviceName << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoClass Class = mpPyDispatcher->onQueryDeviceClass(*pWatchee);
		switch (Class) {
		case GIZMO_CLASS_ATIX10: {
			shared_ptr<GizmoATIX10> pGizmo(new GizmoATIX10(*pWatchee, mGizmos.size(), getGizmoClassID(GIZMO_CLASS_ATIX10)));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_LIRC: {
			shared_ptr<GizmoLIRC> pGizmo(new GizmoLIRC(*pWatchee, mGizmos.size(), getGizmoClassID(GIZMO_CLASS_LIRC)));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_POWERMATE: {
			shared_ptr<GizmoPowermate> pGizmo(new GizmoPowermate(*pWatchee, mGizmos.size(), getGizmoClassID(GIZMO_CLASS_POWERMATE)));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		case GIZMO_CLASS_STANDARD: {
			shared_ptr<GizmoStandard> pGizmo(new GizmoStandard(*pWatchee, mGizmos.size(), getGizmoClassID(GIZMO_CLASS_STANDARD)));
			mGizmos.insert(make_pair(pWatchee->FileName, pGizmo));
			mpPyDispatcher->onRegisterDevice(pGizmo.get());
			break; }
		}
	} catch (error_already_set) {
		PyErr_Print();
		throw H::Exception("Failed to call GizmodDispatcher.onRegisterDevice for onFileEventRegister", __FILE__, __FUNCTION__, __LINE__);
	}
}

/**
 * \brief Event called when the class will begin watching for events (and blocking)
 */
void GizmoDaemon::onFileEventWatchBegin() {
}

/**
 * \brief Event called when the class has ended watching for events (and done blocking)
 */
void GizmoDaemon::onFileEventWatchEnd() {
}

/**
 * \brief  Event triggered on a Focus In
 * \param  Event The Focus Event
 */
void GizmoDaemon::onFocusIn(X11FocusEvent const & Event) {
	if (mShuttingDown)
		return;
	
	//cdbg << "Current Focus: " << Event.WindowName << " [" << Event.WindowNameFormal << "] <" << Event.WindowClass << ">" << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		mCurrentFocus = Event;
		GizmoEventWindowFocus FocusEvent(Event);
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&FocusEvent);
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onFocusIn" << endl;
	}
}

/**
 * \brief  Event triggered on a Focus Out
 * \param  Event The Focus Event
 */
void GizmoDaemon::onFocusOut(X11FocusEvent const & Event) {
	if (mShuttingDown)
		return;
	
	//cdbg << "Leaving Focus: " << Event.WindowName << " [" << Event.WindowNameFormal << "] <" << Event.WindowClass << ">" << endl;
	try {
		mutex::scoped_lock lock(mMutexScript);
		GizmoEventWindowFocus FocusEvent(Event);
		if (!mLocalDisabled)
			mpPyDispatcher->onEvent(&FocusEvent);
	} catch (error_already_set) {
		PyErr_Print();
		cerr << "Failed to call GizmodDispatcher.onEvent for onFocusOut" << endl;
	}
}

/**
 * \brief Signal handler for SEGV
 */
void GizmoDaemon::onSignalSegv() {
	cerr << "Segmentation Fault Detected" << endl;
	signalShutdown();
}

/**
 * \brief Signal handler for INT
 */
void GizmoDaemon::onSignalInt() {
	cdbg << "Keyboard Interrupt Received..." << endl;
	signalShutdown();
}

/**
 * \brief Signal handler for HUP
 */
void GizmoDaemon::onSignalHup() {
	cout << "HUP signal received, reloading config..." << endl;
	mReloadConfig = true;
	signalShutdown();
}

/**
 * \brief Signal handler for QUIT
 */
void GizmoDaemon::onSignalQuit() {
	cdbg << "Request to Quit Received..." << endl;
	signalShutdown();
}

/**
 * \brief Signal handler for KILL
 */
void GizmoDaemon::onSignalKill() {
	cdbg << "Kill signal Received..." << endl;
	signalShutdown();
}

/**
 * \brief Signal handler for TERM
 */
void GizmoDaemon::onSignalTerm() {
	cdbg << "Request to Terminate Received..." << endl;
	signalShutdown();
}

/**
 * \brief Signal handler for STOP
 */
void GizmoDaemon::onSignalStop() {
	cdbg << "Request to Stop Received..." << endl;
	signalShutdown();
}

/**
 * \brief Signal handler for Unknown Signals
 */
void GizmoDaemon::onSignalUnknown(int Signal) {
	cerr << "Unhandled Unknown Signal" << endl;
}

/**
 * \brief  Event triggered when a new connection is detected
 * \param  socket The new socket
 */
void GizmoDaemon::onSocketClientConnect(Socket const & socket) {
	cdbg << "Successfully Connected to [" << mClientHost << "] at Port [" << mClientPort << "]" << endl;
}

/**
 * \brief  Event triggered on a socket disconnect
 * \param  socket The socket
 */
void GizmoDaemon::onSocketClientDisconnect(Socket const & socket) {
	cdbg << "Disconnected from Server" << endl;
}

/** 
 * \brief  Event triggered on a socket server message
 * \param  socket The Socket that triggered the event
 * \param  Message The message
 */
void GizmoDaemon::onSocketClientMessage(Socket const & socket, std::string const & Message) {
	cdbg << "Client Socket Message [" << Message.length() << "] Bytes -- " << Message << endl;
}

/**
 * \brief  Event triggered on a socket read
 * \param  socket The socket
 * \param  ReadBuffer The data
 */
void GizmoDaemon::onSocketClientRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer) {
	cdbg << "Client Socket Read [" << ReadBuffer.length() << "] Bytes" << endl;
}

/**
 * \brief  Event triggered when a new connection is detected
 * \param  pSocket The new socket
 */
void GizmoDaemon::onSocketServerConnect(boost::shared_ptr<Socket> pSocket) {
	cdbg << "Client Connection from [" << pSocket->getAddress() << "]" << endl;
}

/**
 * \brief  Event triggered on a socket disconnect
 * \param  socket The socket
 */
void GizmoDaemon::onSocketServerDisconnect(Socket const & socket) {
	cdbg << "Client Disconnected [" << socket.getAddress() << "]" << endl;
}

/** 
 * \brief  Event triggered on a socket server message
 * \param  socket The Socket that triggered the event
 * \param  Message The message
 */
void GizmoDaemon::onSocketServerMessage(Socket const & socket, std::string const & Message) {
	if (mShuttingDown)
		return;
	
	//cdbg << "Socket Message [" << Message.length() << "] Bytes -- " << Message << endl;
	size_t dPos = Message.find("|");
	if (dPos == string::npos) {
		cdbg << "Invalid Message Received from Client [" << socket.getAddress() << "]" << endl;
		return;
	}
	
	int MessageType;
	try {
		 MessageType = lexical_cast<int>(Message.substr(0, dPos));
	} catch (bad_lexical_cast const & e) {
		cdbg << "Invalid Message Type Received from Client [" << socket.getAddress() << "]" << endl;
		return;
	}
	
	// make sure event class isn't all wacky
	if ( (MessageType < 0) || (MessageType > GIZMO_EVENTCLASS_MAX) ) {
		cdbg << "Improper Message Type Received from Client [" << socket.getAddress() << "]" << endl;
		return;
	}
	
	// everything is okay, let's deserialize
	deserializeMessage(static_cast<GizmoEventClass>(MessageType), Message.substr(dPos + 1));
}

/**
 * \brief  Event triggered on a socket read
 * \param  socket The socket
 * \param  ReadBuffer The data
 */
void GizmoDaemon::onSocketServerRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer) {
	//cdbg4 << "Socket Read [" << ReadBuffer.length() << "] Bytes" << endl;
}

/**
 * \brief  Register all the system devices with Gizmo Daemon
 * 
 * This function creates a registry of all the attached devices
 * and inserts them into Python for use by the user
 */
void GizmoDaemon::registerDevices() {
	cout << "Registering Devices:" << endl << endl;
	
	// register input event devices
	registerInputEventDevices();
	
	// register the LIRC device
	registerLircDevice();
	
	// aesthetics
	cout << endl;
}

/**
 * \brief  Register all of the input event devices with Gizmo Daemon
 */
void GizmoDaemon::registerInputEventDevices() {
	cdbg1 << "Registering Input Event Devices in [" << mEventsDir << "]" << endl;
	path EventsDirPath(mEventsDir);
	if (!filesystem::exists(EventsDirPath))
		throw H::Exception("Input Event dir [" + mEventsDir + "] does NOT exist or permissions are wrong!", __FILE__, __FUNCTION__, __LINE__);
	
	// register the directory itself
	addFileToWatch(mEventsDir, WATCH_INOUT);
	
	// now register the event nodes
	// get a file listing
	std::vector<string> eventsFiles;
	directory_iterator endItr;
	for (directory_iterator iter(mEventsDir); iter != endItr; iter ++) {
		if ( (!filesystem::is_directory(*iter)) && (!filesystem::symbolic_link_exists(*iter)) ) {
			if (iter->leaf().find("event") != 0)
				continue;
			eventsFiles.push_back(mEventsDir + "/" + iter->leaf());
		}
	}
	
	// sort the list of input event nodes
	sort_all(eventsFiles);
	apply_func_args(eventsFiles, &FileEventWatcher::addFileToWatch, this, WATCH_INOUT, "Unknown");
}

/**
 * \brief  Register the LIRC device
 */
void GizmoDaemon::registerLircDevice() {
	cdbg1 << "Registering LIRC device node [" << mLircDev << "]" << endl;
	path LircDevPath(mLircDev);
	if (!filesystem::exists(LircDevPath)) {
		cdbg << "LIRC device node [" + mLircDev + "] does not exist -- disabling LIRC support" << endl;
		return;
	}
	
	boost::shared_ptr<FileWatchee> pWatchee = addUnixSocketToWatch(mLircDev, "LIRC");
	if (!pWatchee) {
		cdbg << "Could not connect to LIRC device node [" + mLircDev + "] -- disabling LIRC support" << endl;
		cdbg << "    - Check permissions" << endl;
		cdbg << "    - Ensure lircd is running" << endl;
		return;
	}
}

/**
 * \brief  Set the config directory
 */
void GizmoDaemon::setConfigDir() {
	// get the hoome directory
	string HomeScriptDir = HOME_SCRIPT_DIR;
	char * EnvHome = getenv("HOME");
	if (EnvHome)
		replace_all(HomeScriptDir, "~", EnvHome);
	
	// make sure it's okay
	bool PathsOkay;
	try {
		path HomeScriptPath(HomeScriptDir);
		PathsOkay = true;
	} catch (filesystem_error const & e) {
		PathsOkay = false;
	}
	
	// set the path
	if ( PathsOkay && filesystem::exists(HomeScriptDir) && filesystem::exists(HomeScriptDir + USER_SCRIPT_DIR) ) {
		mConfigDir = HomeScriptDir;
	} else {
		mConfigDir = SCRIPT_DIR;
		replace_all(mConfigDir, "${prefix}", PREFIX);
	}
}

/**
 * \brief  Set the version information
 */
void GizmoDaemon::setVersionInfo() {
	string Version = VERSION;
	size_t cPos = Version.find(":");
	if (cPos == string::npos)
		cPos = Version.find(".");
	if (cPos == string::npos) {
		mVersionMajor = 0;
		mVersionMinor = 0;
	} else {
		try {
			mVersionMajor = lexical_cast<int>(Version.substr(0, cPos));
			mVersionMinor = lexical_cast<int>(Version.substr(cPos + 1));
		} catch (bad_lexical_cast const & e) {
			mVersionMajor = 0;
			mVersionMinor = 0;
			return;
		}
	}
	
	mVersion = double(mVersionMajor) + (double(mVersionMinor) / 10.0);
}

/**
 * \brief  Shutdown Gizmo Daemon
 */
void GizmoDaemon::signalShutdown() {
	mShuttingDown = true;
	FileEventWatcher::shutdown();
}
