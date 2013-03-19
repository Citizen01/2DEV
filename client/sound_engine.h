#pragma once

#include "engine.h"

class sound_engine : public engine
{
public:
	sound_engine(Game*);
	~sound_engine(void);

	void frame();
};

