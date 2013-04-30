#include "sound_engine.h"
#include "graphics_engine.h"

sound_engine::sound_engine(game* g) : engine(g)
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

void sound_engine::on_engines_linked()
{
	soundrcvr = new SoundEventListener();
	gfxe->getEventListener()->subscribeSoundEngine(soundrcvr);
}