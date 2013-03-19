#pragma once

#include "engine.h"

class game_engine : public engine
{
public:
	game_engine(Game*);
	~game_engine(void);

	void frame();
};

