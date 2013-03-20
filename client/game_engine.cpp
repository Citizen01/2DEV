#include "game_engine.h"


game_engine::game_engine(game* g) : engine(g)
{

}


game_engine::~game_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void game_engine::frame()
{
	//Do stuff
}