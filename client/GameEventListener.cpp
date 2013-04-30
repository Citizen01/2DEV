#include "GameEventListener.h"
#include <iostream>

using namespace std;

GameEventListener::GameEventListener(void)
{
}


GameEventListener::~GameEventListener(void)
{
}

bool GameEventListener::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	cout << "g ";//preuve de la réception des events

	return false;
}
