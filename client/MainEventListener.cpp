#include "MainEventListener.h"
#include <iostream>

using namespace std;

MainEventListener::MainEventListener(Application* ap)
{
	app = ap;
}


MainEventListener::~MainEventListener(void)
{
}

bool MainEventListener::OnEvent(const irr::SEvent& e)
{
	app->getGameEngine()->OnEvent(e);
	app->getGraphicEngine()->OnEvent(e);
	app->getSoundEngine()->OnEvent(e);
	app->getNetworkEngine()->OnEvent(e);

	return false;
}