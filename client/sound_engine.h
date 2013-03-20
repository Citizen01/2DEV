#pragma once

#include "engine.h"

class engine;

class sound_engine : public engine
{
public:
	sound_engine(game*);
	~sound_engine(void);

	void frame();
};

