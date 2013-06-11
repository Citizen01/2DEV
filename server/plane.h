#pragma once

#include <string>

#include <irrlicht.h>
#include "RakString.h"

class Faction;
class Player;

class Plane
{
private:

	Player* m_Pilot;

	std::string _name; //nom du model de l'avion
	irr::scene::IAnimatedMeshSceneNode* _model;

	int EnginePower;
	int MaxEnginePower;

	int Speed;
	int StallSpeed;

	int FuelLoad;
	int MaxFuelLoad;
	
public:

	Plane(Player* pilot, std::string name, irr::scene::ISceneManager* sceneManager);
	~Plane(void);

	void loadMesh(irr::scene::ISceneManager* sceneManager);

	inline std::string getName() { return _name; }
	RakNet::RakString GetRakName();

	int GetEnginePower();
	void SetEnginePower(int enginePower);

	void IncrementEnginePower();
	void DecrementEnginePower();

	inline irr::scene::IAnimatedMeshSceneNode* getMesh() { return _model; }

	inline irr::core::vector3df getPosition() { return _model->getPosition(); }
	inline irr::core::vector3df getRotation() { return _model->getRotation(); }

	int GetSpeed();
	void SetSpeed(int speed);

	int GetStallSpeed();

	int GetMaxEnginePower();

	int GetFuelLoad();
	void SetFuelLoad(int fuel);

	int GetMaxFuelLoad();
};

