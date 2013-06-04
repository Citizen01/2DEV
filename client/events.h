#pragma once

#include "Event_OnBindedKeyHited.h"

enum EVENT_TYPE
{
	onBindedKeyHited,

	onPlayerJoin,
	onPlayerQuit,
	onPlayerFire,
	onPlayerLockedSomeone,

	onProjectileHit,
	
	onPlaneExplode,
	onEngineStop,
	onEngineStart,

	EVENTS_TYPE_COUNT
};