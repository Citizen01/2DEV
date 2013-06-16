#include "plane.h"

#include "GLOBALS.h"
#include "server.h"
#include "physic_engine.h"
#include "faction.h"
#include "player.h"

using namespace std;
using namespace irr;
using namespace RakNet;

using namespace constants;

Plane::Plane(Player* pilot, std::string name)
{
	objectType = 2;

	m_Pilot = pilot;

	//Crée un avion en fonction du nom de ce dernier
	m_Name = name;

	loadMesh(); //Chargement du modèle 3d
	
	physics_engine::getSingleton()->addPlane(this);

	m_EnginePower = 0;
	m_MaxEnginePower = 1000;
	
	m_StallSpeed = 100;
	m_MaxSpeed = 1000;

	m_MaxFuelLoad = 100;
	m_FuelLoad = m_MaxFuelLoad;

	m_MaxLife = 100;
	m_Life = m_MaxLife;
}

Plane::~Plane(void)
{
}

void Plane::loadMesh()
{	
	std::string modefile = constants::PATH_TO_MEDIA + "/planes/" + m_Name + "/" + m_Name + ".3DS";
	m_Model = Server::getSingleton()->getSceneManager()->addAnimatedMeshSceneNode(Server::getSingleton()->getSceneManager()->getMesh(modefile.c_str()));
	
	m_Model->setPosition(m_Pilot->getFaction()->getPosition());
	m_Model->setRotation(m_Pilot->getFaction()->getRotation());
}

void Plane::incrementEnginePower()
{
	m_EnginePower ++;
	if(m_EnginePower > m_MaxEnginePower)
	{
		m_EnginePower = m_MaxEnginePower;
	}
}

void Plane::decrementEnginePower()
{
	m_EnginePower --;
	if(m_EnginePower < 0)
	{
		m_EnginePower = 0;
	}
}