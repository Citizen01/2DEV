#include "game_engine.h"

#include <iostream>

#include "GLOBALS.h"
#include "utils.h"
#include "app.h"
#include "particle_manager.h"

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
		//cout << "Réception d'un EET_USER_EVENT ..." << endl;

		string* type = (string*)event.UserEvent.UserData1;
		//cout << "Le type de l'event est :" << *type << endl;

		if (*type == "ACTION"){
			ACTION_CODE act = (ACTION_CODE)event.UserEvent.UserData2;
			//cout << "Valeur de l'action: " << act << endl;

			switch (act)
			{
			case ACCELERATE:
				//TODO
				ne->askToAccelerate();
				//moveNodeInLocalSpace(plane, irr::core::vector3df(0,0,1), 17.0f);
				break;
			case DECELERATE:
				{
					scene::ICameraSceneNode* cam = gfxe->getSceneManager()->addCameraSceneNodeFPS(0, 100, 0.1);
					cam->setFarValue(42000);
					ne->askToDecelerate();
				}
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
				//rotateNodeInLocalSpace(plane, 3.f, irr::core::vector3df(1,0,0));
				break;
			case STRAIGHTEN:
				//TODO
				//rotateNodeInLocalSpace(plane, -3.f, irr::core::vector3df(1,0,0));
				break;
			case ROLL_LEFT:
				//TODO
				//rotateNodeInLocalSpace(plane, 3.f, irr::core::vector3df(0,0,1));
				break;
			case ROLL_RIGHT:
				//TODO
				//rotateNodeInLocalSpace(plane, -3.f, irr::core::vector3df(0,0,1));
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
				particle_manager::getSingleton()->createParticleEmitter(PARTICLE_EXPLOSION, core::vector3df(0, 0, 0));
				break;
			default:
				//Nothing
				break;
			}
		}

	}
	return false;
}
