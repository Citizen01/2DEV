#pragma once

#include "engine.h"
#include "GameEventListener.h"

class engine;
class game;

class game_engine : public engine
{
private:
	GameEventListener* gamercvr;

public:
	game_engine(game*);
	~game_engine(void);

	void frame();

	void on_engines_linked();
};

