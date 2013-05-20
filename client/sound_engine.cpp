#include "sound_engine.h"
#include "graphics_engine.h"
#include <iostream>

using namespace std;

sound_engine::sound_engine(App* ap) : engine(ap)
{
}


sound_engine::~sound_engine(void)
{
}


//Implémentation de la méthode virtuelle pure héritée de la classe engine
void sound_engine::frame()
{
	//Do stuff
}

bool sound_engine::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	return false;
}
