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


//Impl�mentation de la m�thode virtuelle pure h�rit�e de la classe engine
void sound_engine::frame()
{
	//Do stuff
}

bool sound_engine::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	return false;
}
