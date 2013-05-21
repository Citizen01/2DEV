#include "game_engine.h"
#include "graphics_engine.h" //pour gfxe
#include <iostream>

using namespace std;

game_engine::game_engine()
{
}


game_engine::~game_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void game_engine::frame()
{

}

bool game_engine::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	return false;
}
