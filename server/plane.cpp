#include "plane.h"

#include "GLOBALS.h"
#include "utils.h"
#include "server.h"

#include "faction.h"
#include "player.h"

using namespace irr;
using namespace RakNet;

Plane::Plane(Player* pilot, std::string name, scene::ISceneManager* sceneManager)
{
	m_Pilot = pilot;
	//Crée un avion en fonction du nom de ce dernier
	_name = name;

	loadMesh(sceneManager); //Chargement du modèle 3d

	EnginePower = 0;
	MaxEnginePower = 10;
}

Plane::~Plane(void)
{
}


void Plane::loadMesh(scene::ISceneManager* sceneManager)
{	
	std::string modefile = constants::PATH_TO_MEDIA + "/planes/SU 25/SU 25.3DS";
	_model = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh(modefile.c_str()));
	
	_model->setPosition(m_Pilot->GetFaction()->GetPosition());
	_model->setRotation(m_Pilot->GetFaction()->GetRotation());
}

RakString Plane::GetRakName()
{
	return RakString(_name.c_str());
}

int Plane::GetEnginePower()
{
	return EnginePower;
}

void Plane::IncrementEnginePower()
{
	EnginePower ++;
	if(EnginePower > MaxEnginePower)
	{
		EnginePower = MaxEnginePower;
	}
}

void Plane::DecrementEnginePower()
{
	EnginePower --;
	if(EnginePower < 0)
	{
		EnginePower = 0;
	}
}