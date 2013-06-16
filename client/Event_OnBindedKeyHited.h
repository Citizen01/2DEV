#pragma once

#include "GLOBALS.h"
#include <irrlicht.h>

struct ev_onBindedKeyHited
{
	constants::ACTION_CODE actionCode;
	bool pressedDown;
};