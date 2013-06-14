#include "plane.h"

#include "GLOBALS.h"
#include "utils.h"
#include "App.h"

#include "faction.h"
#include "player.h"

using namespace irr;
using namespace RakNet;

Plane::Plane(Player* pilot, std::string name)
{
	m_Pilot = pilot;
	//Crée un avion en fonction du nom de ce dernier
	_name = name;

	loadMesh(); //Chargement du modèle 3d
	App::getSingleton()->getSoundEngine()->attach3DSound("reactor.mp3",this->getMesh(),10.0f,250.0f);
	EnginePower = 0;
	MaxEnginePower = 10;
}

Plane::~Plane(void)
{
}

void Plane::loadMesh()
{
	scene::ISceneManager* smgr = App::getSingleton()->getGraphicEngine()->getSceneManager();
	std::string modefile = constants::PATH_TO_MEDIA + "/planes/SU 25/SU 25.3DS";
	_model = smgr->addAnimatedMeshSceneNode(smgr->getMesh(modefile.c_str()));
  
	//On met l'auto-éclairage (debug)
	_model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
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
void Plane::SetPosition(irr::core::vector3df position)
{
	_model->setPosition(position);
	if(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer() == m_Pilot)
	{
		m_Pilot->updateThirdView();
	}
}

void Plane::SetRotation(irr::core::vector3df rotation)
{
	_model->setRotation(rotation);
	if(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer() == m_Pilot)
	{
		m_Pilot->updateThirdView();
	}
}