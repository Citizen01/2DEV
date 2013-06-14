#include "game_engine.h"

#include <iostream>

#include "GLOBALS.h"
#include "utils.h"
#include "app.h"
#include "events.h"

using namespace std;
using namespace irr;
using namespace constants;

game_engine::game_engine()
{
	m_Game = NULL;
}

game_engine::~game_engine(void)
{
}

void game_engine::LaunchGame(string mapName)
{
	m_Game = new game(mapName);
}

game* game_engine::GetGame()
{
	return m_Game;
}

void game_engine::StopGame()
{
	delete m_Game;
	m_Game = NULL;
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void game_engine::frame()
{
}

bool game_engine::OnEvent(const SEvent& event)
{
	//Handle events here:
	if (event.EventType == EET_USER_EVENT)
	{
		int type = event.UserEvent.UserData1;

		if (type == EVENT_TYPE::onBindedKeyHited){
			ev_onBindedKeyHited* args = (ev_onBindedKeyHited*)event.UserEvent.UserData2;

			ACTION_CODE act = args->actionCode;

			switch (act)
			{
			case ACCELERATE:
				//TODO
				ne->askToAccelerate();
				break;
			case DECELERATE:
				ne->askToDecelerate();
				//TODO
				break;
			case LEFT:
				//TODO
				break;
			case RIGHT:
				//TODO
				break;
			case DIVE:
				//TODO
				break;
			case STRAIGHTEN:
				//TODO
				break;
			case ROLL_LEFT:
				//TODO
				break;
			case ROLL_RIGHT:
				//TODO
				break;
			case PRIMARY_FIRE:
				//TODO
				break;
			case SECONDARY_FIRE:
				//TODO
				break;
			case EQUIPMENT:
				//TODO
				ne->GetReady();
				break;
			case TOGGLEMENU:
				//TODO
				break;
			default:
				//Nothing
				break;
			}
		}

	}
	return false;
}
