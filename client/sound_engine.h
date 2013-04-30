#pragma once

#include "engine.h"
#include "SoundEventListener.h"

class engine;

class sound_engine : public engine
{
private:
	SoundEventListener* soundrcvr;

public:
	sound_engine(game*);
	~sound_engine(void);

	void frame();

	void on_engines_linked();
};

