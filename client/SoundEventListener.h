#pragma once
#include <irrlicht.h>

class SoundEventListener :
	public irr::IEventReceiver
{

public:
	SoundEventListener(void);
	~SoundEventListener(void);

	bool OnEvent(const irr::SEvent& event);
};

