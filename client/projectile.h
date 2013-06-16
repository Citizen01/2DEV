#pragma once

#include "NetworkIDManager.h"
#include "RakString.h"

#include <irrlicht.h>

#include "GLOBALS.h"
#include "app.h"

class Player;

class Projectile : public RakNet::NetworkIDObject
{
public:

	Projectile(Player* owner, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID, RakNet::RakString modelFile);
	~Projectile();

	inline Player* getOwner() { return m_Owner; }
	
	void loadMesh(RakNet::RakString modelFile);
	inline irr::scene::IAnimatedMeshSceneNode* getMesh() { return m_Model; }
	
	inline irr::core::vector3df getPosition() { return m_Model->getPosition(); }
	inline void setPosition(irr::core::vector3df position) { m_Model->setPosition(position); }
	inline irr::core::vector3df getRotation() { return m_Model->getRotation(); }
	inline void setRotation(irr::core::vector3df rotation) { m_Model->setRotation(rotation); }

private:

	Player* m_Owner;

	irr::scene::IAnimatedMeshSceneNode* m_Model;
};