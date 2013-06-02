#include "game_engine.h"
#include "GLOBALS.h"
#include "utils.h"
#include <iostream>

using namespace std;
using namespace irr;
using namespace constants;

game_engine::game_engine()
{
}


game_engine::~game_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void game_engine::frame()
{

}

//TODO: A supprimer àprès le passage de Plane* joueur dans game
void game_engine::setPlane(Plane* pl)
{
	if (pl != NULL)
		joueur = pl;
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

			//TODO: A bouger dans game:
			scene::IAnimatedMeshSceneNode* plane = joueur->getMesh();
			switch (act)
			{
			case constants::ACCELERATE:
				//TODO
				moveNodeInLocalSpace(plane, irr::core::vector3df(0,0,1), 17.0f);
				break;
			case constants::DECELERATE:
				//TODO
				break;
			case constants::LEFT:
				//TODO
				
				break;
			case constants::RIGHT:
				//TODO
				break;
			case constants::DIVE:
				//TODO
				rotateNodeInLocalSpace(plane, 3.f, irr::core::vector3df(1,0,0));
				break;
			case constants::STRAIGHTEN:
				//TODO
				rotateNodeInLocalSpace(plane, -3.f, irr::core::vector3df(1,0,0));
				break;
			case constants::ROLL_LEFT:
				//TODO
				rotateNodeInLocalSpace(plane, 3.f, irr::core::vector3df(0,0,1));
				break;
			case constants::ROLL_RIGHT:
				//TODO
				rotateNodeInLocalSpace(plane, -3.f, irr::core::vector3df(0,0,1));
				break;
			case constants::PRIMARYFIRE:
				//TODO
				break;
			case constants::SECONDARYFIRE:
				//TODO
				break;
			case constants::EQUIPMENT:
				//TODO
				break;
			case constants::TOGGLEMENU:
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
