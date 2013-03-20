#pragma once

#include "engine.h"

class engine;
class game;

class game_engine : public engine
{
public:
	game_engine(game*);
	~game_engine(void);

	void frame();
};

