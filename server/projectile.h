#pragma once

#include "NetworkIDManager.h"
#include "RakString.h"

#include <irrlicht.h>

#include "GLOBALS.h"
#include "server.h"
#include "collidableObject.h"

class Player;
class Plane;

class Projectile : public collidableObject, public RakNet::NetworkIDObject
{
public:

	Projectile(Player* owner, RakNet::NetworkIDManager* networkIDManager, RakNet::RakString modelFile, unsigned int timeToLive, int speed, Plane* target = NULL);
	~Projectile();

	inline Player* getOwner() { return m_Owner; }

	inline Plane* getTarget() { return m_Target; }
	
	void loadMesh(RakNet::RakString modelFile);
	inline irr::scene::IAnimatedMeshSceneNode* getMesh() { return m_Model; }

	inline irr::scene::ISceneNode* getNode() { return static_cast<irr::scene::ISceneNode*>(m_Model);  }

	inline RakNet::RakString getModelType() { return m_ModelType; }
	
	inline btRigidBody* getBody() { return m_Body; }
	inline void setBody(btRigidBody* body) { m_Body = body; }
	
	inline irr::core::vector3df getPosition() { return m_Model->getPosition(); }
	inline irr::core::vector3df getRotation() { return m_Model->getRotation(); }

	inline unsigned int getTimeToLive() { return m_TimeToLive; }
	void updateTimeToLive(unsigned int deltaTime);

	inline int getSpeed() { return m_Speed; }

private:

	Player* m_Owner;

	Plane* m_Target;

	irr::scene::IAnimatedMeshSceneNode* m_Model;

	RakNet::RakString m_ModelType;

	btRigidBody* m_Body;

	unsigned int m_TimeToLive;
	
	int m_Speed;
};