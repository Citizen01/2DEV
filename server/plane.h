#pragma once

#include <string>

#include "RakString.h"

#include <irrlicht.h>

#include <btBulletDynamicsCommon.h>

class Faction;
class Player;

class Plane
{
private:

	Player* m_Pilot;

	std::string m_Name; //nom du model de l'avion
	irr::scene::IAnimatedMeshSceneNode* m_Model;

	btRigidBody* m_Body;

	int m_EnginePower;
	int m_MaxEnginePower;
	
	int m_StallSpeed;
	int m_MaxSpeed;

	int m_FuelLoad;
	int m_MaxFuelLoad;
	
public:

	Plane(Player* pilot, std::string name);
	~Plane(void);

	void loadMesh();

	inline std::string getName() { return m_Name; }
	inline RakNet::RakString getRakName() { return RakNet::RakString(m_Name.c_str()); }

	inline irr::scene::IAnimatedMeshSceneNode* getMesh() { return m_Model; }

	inline irr::core::vector3df getPosition() { return m_Model->getPosition(); }
	inline irr::core::vector3df getRotation() { return m_Model->getRotation(); }

	inline btRigidBody* getBody() { return m_Body; }
	inline void setBody(btRigidBody* body) { m_Body = body; }

	inline int getEnginePower() { return m_EnginePower; }
	inline void setEnginePower(int enginePower) { m_EnginePower = enginePower; }

	void incrementEnginePower();
	void decrementEnginePower();

	inline int getMaxEnginePower() { return m_MaxEnginePower; }
	
	inline int getStallSpeed() { return m_StallSpeed; }
	inline int getMaxSpeed() { return m_MaxSpeed; }

	inline int getFuelLoad() { return m_FuelLoad; }
	inline void setFuelLoad(int fuel) { m_FuelLoad = fuel; }

	inline int getMaxFuelLoad() { return m_MaxFuelLoad; }
};

