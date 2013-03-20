#pragma once

#include <string>
#include "game_engine.h"
#include "graphics_engine.h"
#include "network_engine.h"
#include "sound_engine.h"

using namespace irr;

class game_engine;
class graphics_engine;
class network_engine;
class sound_engine;

class game
{
private:
	//Les différents modules qui compose le jeu
	game_engine* g;
	graphics_engine* gfx;
	network_engine* n;
	sound_engine* s;
	
public:
	game();
	~game();

	//Démarre une partie sur <mapname>
	void play(std::string mapname);

	//// GETTERS ////
	inline game_engine* getGameEngine() { return g; }
	inline graphics_engine* getGraphicEngine() { return gfx; }
	inline network_engine* getNetworkEngine() { return n; }
	inline sound_engine* getSoundEngine() { return s; }
};

