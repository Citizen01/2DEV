#include "game_engine.h"


game_engine::game_engine(Game* g) : engine(g)
{

}


game_engine::~game_engine(void)
{
}

//Impl�mentation de la m�thode virtuelle pure h�rit�e de la classe engine
void sound_engine::frame()
{
	//Do stuff
}