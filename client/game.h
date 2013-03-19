#pragma once

#include "game_engine.h"
#include "graphics_engine.h"
#include "network_engine.h"
#include "sound_engine.h"

class Game
{
private:
	//Les différents modules qui compose le jeu
	game_engine *g;
	graphics_engine *gfx;
	network_engine *n;
	sound_engine *s;
	
public:
	Game();
	~Game();
};

