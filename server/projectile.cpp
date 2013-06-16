#include "projectile.h"

#include "physic_engine.h"
#include "player.h"
#include "plane.h"

using namespace irr;
using namespace RakNet;
using namespace std;

Projectile::Projectile(Player* owner, NetworkIDManager* networkIDManager, RakString modelFile, unsigned int timeToLive, int speed, Plane* target)
{
	m_Owner = owner;
	
	this->SetNetworkIDManager(networkIDManager);
	this->GetNetworkID();

	loadMesh(modelFile);

	m_ModelType = modelFile;

	m_Speed = speed;

	physics_engine::getSingleton()->addProjectile(this);

	m_TimeToLive = timeToLive;


	m_Target = target;
}

Projectile::~Projectile()
{
	m_Model->remove();
}

void Projectile::loadMesh(RakString modelFile)
{
	m_Model = Server::getSingleton()->getSceneManager()->addAnimatedMeshSceneNode(Server::getSingleton()->getSceneManager()->getMesh((constants::PATH_TO_MEDIA + "/projectiles/" + modelFile.C_String() + "/" + modelFile.C_String() + ".3DS").c_str()));
	
	m_Model->setPosition(m_Owner->getPlane()->getPosition() + core::vector3df(0, 0, 10));
	m_Model->setRotation(m_Owner->getPlane()->getRotation());
}

void Projectile::updateTimeToLive(unsigned int deltaTime)
{
	m_TimeToLive -= deltaTime;
	if(m_TimeToLive <= 0)
	{
		this->~Projectile();
	}
}