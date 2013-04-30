#include "game_engine.h"
#include "graphics_engine.h" //pour gfxe

game_engine::game_engine(game* g) : engine(g)
{
}


game_engine::~game_engine(void)
{
}

//Impl�mentation de la m�thode virtuelle pure h�rit�e de la classe engine
void game_engine::frame()
{
	//Do stuff
}

void game_engine::on_engines_linked() 
{
	gamercvr = new GameEventListener();
	gfxe->getEventListener()->subscribeGameEngine(gamercvr);
}