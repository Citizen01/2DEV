#pragma once
#include "ieventreceiver.h"
class GameEventListener :
	public irr::IEventReceiver
{
public:
	GameEventListener(void);
	~GameEventListener(void);

	bool OnEvent(const irr::SEvent& event);

};

