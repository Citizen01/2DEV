#include "game_engine.h"


game_engine::game_engine(Game* g) : engine(g)
{

}


game_engine::~game_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void sound_engine::frame()
{
	//Do stuff
}