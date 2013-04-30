#include "game.h"

network_engine::network_engine(game* g) : engine(g)
{

}

network_engine::~network_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void network_engine::frame()
{
	//Do stuff
}

void network_engine::on_engines_linked() {}