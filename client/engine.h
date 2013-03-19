#pragma once

#include "game.h"

class Engine
{
public:
	Engine(Game*);
	virtual ~Engine();

	//Méthode qui sera implémenté dans les classes filles
	virtual void frame() = 0;

protected:
	Game* parent;

	game_engine *ge;
	network_engine *ne;
	graphics_engine *gfxe;
	sound_engine *se;

};

