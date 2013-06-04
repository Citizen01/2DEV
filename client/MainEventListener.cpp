#include "MainEventListener.h"
#include "app.h"
#include "GLOBALS.h"
#include "events.h"
#include <iostream>

using namespace std;
using namespace constants;

MainEventListener::MainEventListener()
{
}


MainEventListener::~MainEventListener(void)
{
}

bool MainEventListener::OnEvent(const irr::SEvent& e)
{
	listenForBindedKeys(e);
	App::getSingleton()->getGameEngine()->OnEvent(e);
	App::getSingleton()->getGraphicEngine()->OnEvent(e);
	App::getSingleton()->getSoundEngine()->OnEvent(e);
	App::getSingleton()->getNetworkEngine()->OnEvent(e);

	return false;
}

void MainEventListener::listenForBindedKeys(const irr::SEvent& e)
{
	if (e.EventType != irr::EET_KEY_INPUT_EVENT)
		return;

	irr::EKEY_CODE kcode = e.KeyInput.Key;
	for each (pair<constants::ACTION_CODE, const irr::EKEY_CODE> pa in App::getSingleton()->binds)
	{
		if (pa.second == kcode)
		{
			string* type = new string("ACTION");

			irr::SEvent ev;
			ev.EventType = irr::EET_USER_EVENT;
			ev.UserEvent.UserData1 = irr::s32(type); //TODO: C'est des putain d'int !!!
			ev.UserEvent.UserData2 = irr::s32(pa.first);

			//cout << "Envoit de l'event ACTION: " << type << endl;

			//On trigger notre event dans le système d'Irrlicht:
			App::getSingleton()->getGraphicEngine()->getDevice()->postEventFromUser(ev);
		}
	}
}