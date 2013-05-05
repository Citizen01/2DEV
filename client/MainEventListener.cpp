#include "MainEventListener.h"
#include <iostream>

using namespace std;

MainEventListener::MainEventListener(game* ga)
{
	g = ga;
}


MainEventListener::~MainEventListener(void)
{
}

bool MainEventListener::OnEvent(const irr::SEvent& e)
{

	g->getGameEngine()->OnEvent(e);
	g->getGraphicEngine()->OnEvent(e);
	g->getSoundEngine()->OnEvent(e);
	g->getNetworkEngine()->OnEvent(e);

	return false;
}