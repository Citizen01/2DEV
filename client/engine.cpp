#include "engine.h"
#include <cstdlib> //Pour NULL

#include "game_engine.h"
#include "graphics_engine.h"
#include "network_engine.h"
#include "sound_engine.h"

engine::engine(Application* ap)
{
	parent = ap;
	ge = NULL;
	ne = NULL;
	gfxe = NULL;
	se = NULL;
}


engine::~engine(void)
{
}


//Implémentation des méthodes pour le linkage des modules
void engine::link_game_engine(game_engine* g) { ge = g; }
void engine::link_graphics_engine(graphics_engine* gfx) { gfxe = gfx; }
void engine::link_network_engine(network_engine* n) { ne = n; }
void engine::link_sound_engine(sound_engine* s) { se = s; }