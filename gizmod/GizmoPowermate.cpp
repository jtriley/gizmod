    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  GizmoPowermate.cpp
*** \brief GizmoPowermate class body
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

#include "GizmoPowermate.hpp"
#include "GizmoEventPowermate.hpp"
#include "GizmoKeyDefs.hpp"
#include "../libH/Debug.hpp"
#include "../libH/Exception.hpp"
#include <boost/shared_ptr.hpp>
#include <errno.h>

using namespace std;
using namespace boost;
using namespace H;

////////////////////////////////////////////////////////////////////////////
// Type Defs
///////////////////////////////////////

/**
 * \def   GIZMO_POWERMATE_TYPE
 * \brief String type of this gizmo
 */
#define GIZMO_POWERMATE_TYPE	"Powermate"

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief GizmoPowermate Default Constructor
 */
GizmoPowermate::GizmoPowermate(const H::DeviceInfo & deviceInfo, int DeviceID, int DeviceClassID) : Gizmo(GIZMO_CLASS_POWERMATE, deviceInfo, DeviceID, DeviceClassID), GizmoLinuxInputDevice(deviceInfo) {
	mRotated = false;
	mPulseAsleep = true;
}

/**
 * \brief GizmoPowermate Destructor
 */
GizmoPowermate::~GizmoPowermate() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Change the state of the Powermate's LED
 * \param  StaticBrightness Brightness level of LED
 * \param  PulseSpeed Pulse speed of the LED
 * \param  PulseTable Pulse type of LED
 * \param  PulseAsleep Pulse while asleep
 * \param  PulseAwake Pulse while awake
 *
 * This function is what sends raw event codes to the Powermate
 * All other functions use this as their base, as this function
 * encompasses the complete functionality of the Powermate.
 */
void GizmoPowermate::changeLEDState(int StaticBrightness, int PulseSpeed, int PulseTable, int PulseAsleep, int PulseAwake) {
	struct input_event ev;
	memset(&ev, 0, sizeof(struct input_event));
	
	StaticBrightness &= 0xFF;

	if (PulseSpeed < 0)
		PulseSpeed = 0;
	else if (PulseSpeed > 510)
		PulseSpeed = 510;
	if (PulseTable < 0)
		PulseTable = 0;
	else if (PulseTable > 2)
		PulseTable = 2;
	PulseAsleep = !!PulseAsleep;
	PulseAwake = !!PulseAwake;

	ev.type = EV_MSC;
	ev.code = MSC_PULSELED;
	ev.value = StaticBrightness | (PulseSpeed << 8) | (PulseTable << 17) | (PulseAsleep << 19) | (PulseAwake << 20);

	if (write(mDeviceInfo.FileDescriptor, &ev, sizeof(struct input_event)) != sizeof(struct input_event))
		cdbg << "Failed to Write to Griffin PowerMate [" << strerror(errno) << "]" << endl;
}

/**
 * \brief  Get the Powermate's LED Value
 * \return LED value (0-255)
 */
unsigned char GizmoPowermate::getLED() {
	return mLevel;
}

/**
 * \brief  Get the Powermate's LED Value as a percentage 
 * \return LED value (0.0-100.0)
 */
float GizmoPowermate::getLEDPercent() {
	return ((float) mLevel / 255.0f) * 100.0f;
}

/**
 * \brief  Get pulse while sleeping
 * \return True if the powermate will pulse when it goes to sleep
 */
bool GizmoPowermate::getLEDPulseAsleep() {
	return mPulseAsleep;
} 

/**
 * \brief  Get the type of this Gizmo
 * \return Type of the Gizmo
 */
std::string GizmoPowermate::getType() {
	return GIZMO_POWERMATE_TYPE;
}

/**
 * \brief  Get whether or not the dial has rotated since the last button event
 * \return True if the dial has moved
 */
bool GizmoPowermate::getRotated() {
	return mRotated;
}

/**
 * \brief  Process an event
 * \param  pEvent The event to process
 * \return True on if the event should get passed on to the script
 */
bool GizmoPowermate::processEvent(GizmoEvent * pEvent) {
	GizmoEventPowermate * pPowermateEvent = static_cast<GizmoEventPowermate *>(pEvent);
	
	switch (pPowermateEvent->Type) {
	case EV_REL:
		mRotated = true;
		break;
	case EV_KEY:
		setKeyState(pPowermateEvent->Code, pPowermateEvent->Value);
		if (pPowermateEvent->Value)
			mRotated = false;
		break;
	default:
		// do nothing
		break;
	}
	
	return true;
}

/**
 * \brief  Set the hardware pulsing state of the Powermate's LED
 * \param  Level The Level of the Pulsing (0x80 is a good value)
 * \param  PulseSpeed Speed of the pulsing
 * \param  PulseTable Type of the pulsing
 */
void GizmoPowermate::pulseLED(int Level, int PulseSpeed, int PulseTable) {
	changeLEDState(Level, PulseSpeed, PulseTable, 1, 1);
	cdbg2 << "Pulsing LED [Speed " << PulseSpeed << " @ Table " << PulseTable << "]" << endl;
}

/**
 * \brief  Set the intensity of the Powermate's LED
 * \param  Level of intensity from 0 - 255
 */
void GizmoPowermate::setLED(unsigned char Level) {
	changeLEDState((int) Level, 255, 0, mPulseAsleep, 0);
	mLevel = Level;
}

/**
 * \brief  Set the intensity of the Powermate's LED as a percentage
 * \param  Percent The intensity of the powermate as a range between 0.0 and 100.0
 */
void GizmoPowermate::setLEDPercent(float Percent) {
	if (Percent < 0.0f)
		Percent = 0.0f;
	else if (Percent > 100.0f)
		Percent = 100.0f;
	setLED( (unsigned char) (255.0f * (Percent / 100.0f)));
}

/**
 * \brief  Set LED pulse while sleeping
 * \param  Enabled Set to true if the powermate should pulse when it goes to sleep
 */
void GizmoPowermate::setLEDPulseAsleep(bool Enabled) {
	mPulseAsleep = Enabled;
} 
