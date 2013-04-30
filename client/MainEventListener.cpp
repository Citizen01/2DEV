#include "MainEventListener.h"
#include <iostream>

using namespace std;

MainEventListener::MainEventListener()
{
	renderer = NULL;
	gListener = NULL;
	sListener = NULL;
}


MainEventListener::~MainEventListener(void)
{
}

bool MainEventListener::OnEvent(const irr::SEvent& e)
{
	//Propagation à CEGUI
	if ( gListener != NULL)
		renderer->injectEvent(e);

	//Propagation au game_engine
	if ( gListener != NULL)
		gListener->OnEvent(e);

	//Propagation au sound_engine
	if ( sListener != NULL)
		sListener->OnEvent(e);


	return false;
}


bool MainEventListener::subscribeCEGUI(CEGUI::IrrlichtRenderer* r)
{
	renderer = r;
	return true;
}

bool MainEventListener::subscribeGameEngine(GameEventListener* g)
{
	gListener = g;
	return true;
}

bool MainEventListener::subscribeSoundEngine(SoundEventListener* s)
{
	sListener = s;
	return true;
}