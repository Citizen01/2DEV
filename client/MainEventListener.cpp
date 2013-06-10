#include "MainEventListener.h"
#include "app.h"
#include "GLOBALS.h"
#include "events.h"
#include <iostream>

using namespace std;
using namespace irr;
using namespace constants;

MainEventListener::MainEventListener()
{
}


MainEventListener::~MainEventListener(void)
{
}

bool MainEventListener::OnEvent(const SEvent& e)
{
	listenForBindedKeys(e);
	App::getSingleton()->getGameEngine()->OnEvent(e);
	App::getSingleton()->getGraphicEngine()->OnEvent(e);
	App::getSingleton()->getSoundEngine()->OnEvent(e);
	App::getSingleton()->getNetworkEngine()->OnEvent(e);

	return false;
}

void MainEventListener::listenForBindedKeys(const SEvent& e)
{
	EKEY_CODE kcode = KEY_KEY_CODES_COUNT;
	if(e.EventType == EET_KEY_INPUT_EVENT && e.KeyInput.PressedDown)
	{
		kcode = e.KeyInput.Key;
	} 
	else if (e.EventType == EET_MOUSE_INPUT_EVENT)
	{
		if (e.MouseInput.isLeftPressed())
			kcode = KEY_LBUTTON;
		else if (e.MouseInput.isRightPressed())
			kcode = KEY_RBUTTON;
		else if(e.MouseInput.isMiddlePressed())
			kcode = KEY_MBUTTON;
		else
			return;
	} 
	else
		return;
	
	for each (pair<constants::ACTION_CODE, const EKEY_CODE> pa in App::getSingleton()->binds)
	{
		if (pa.second == kcode)
		{
			string* type = new string("ACTION");

			SEvent ev;
			ev.EventType = EET_USER_EVENT;
			ev.UserEvent.UserData1 = s32(type); //TODO: C'est des putain d'int !!!
			ev.UserEvent.UserData2 = s32(pa.first);

			//On trigger notre event dans le système d'Irrlicht:
			App::getSingleton()->getGraphicEngine()->getDevice()->postEventFromUser(ev);
			break;
		}
	}
}