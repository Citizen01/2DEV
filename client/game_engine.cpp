#include "game_engine.h"

#include <iostream>

#include "GLOBALS.h"
#include "utils.h"
#include "app.h"
#include "events.h"
#include "particle_manager.h"
#include "ui_windows.h"

using namespace std;
using namespace irr;
using namespace constants;

game_engine::game_engine(App* a) : engine(a)
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
				//TODO
				ne->askToDecelerate();
				break;
			case LEFT:
				//TODO
				break;
			case RIGHT:
				//TODO
				break;
			case DIVE:
				//TODO
				ne->askToDive();
				break;
			case STRAIGHTEN:
				//TODO
				ne->askToStraighten();
				break;
			case ROLL_LEFT:
				//TODO
				ne->askToRollLeft();
				break;
			case ROLL_RIGHT:
				//TODO
				ne->askToRollRight();
				break;
			case PRIMARY_FIRE:
				//TODO: A BOUGER
				App::getSingleton()->getSoundEngine()->play3D("tir.mp3",this->GetGame()->getLocalPlayer()->GetPlane()->getPosition(),10.0f,250.0f);
				//TODO
				break;
			case SECONDARY_FIRE:
				//TODO
				ne->askToShootMissile();
				break;
			case EQUIPMENT:
				//TODO
				ne->GetReady();
				break;
			case TOGGLEMENU:
				{
					toggle_ingame_menu(); 
					//TODO: DELETE HACK
					scene::ICameraSceneNode* cam = gfxe->getSceneManager()->addCameraSceneNodeFPS(0, 50, 0.005);
					cam->setPosition(core::vector3df(0, 2, 0));
				}
				break;
			default:
				//Nothing
				break;
			}
		}

	}
	return false;
}
