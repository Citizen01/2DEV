#include "MainEventListener.h"
#include <iostream>

using namespace std;

MainEventListener::MainEventListener()
{
}


MainEventListener::~MainEventListener(void)
{
}

bool MainEventListener::OnEvent(const irr::SEvent& e)
{
	App::getSingleton()->getGameEngine()->OnEvent(e);
	App::getSingleton()->getGraphicEngine()->OnEvent(e);
	App::getSingleton()->getSoundEngine()->OnEvent(e);
	App::getSingleton()->getNetworkEngine()->OnEvent(e);

	return false;
}