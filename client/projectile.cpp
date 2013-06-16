#include "projectile.h"

#include "player.h"

using namespace irr;
using namespace RakNet;
using namespace std;

Projectile::Projectile(Player* owner, NetworkIDManager* networkIDManager, NetworkID networkID, RakString modelFile)
{
	m_Owner = owner;
	
	this->SetNetworkIDManager(networkIDManager);
	this->SetNetworkID(networkID);

	loadMesh(modelFile);
}

Projectile::~Projectile()
{
	m_Model->remove();
}

void Projectile::loadMesh(RakString modelFile)
{
	m_Model = App::getSingleton()->getGraphicEngine()->getSceneManager()->addAnimatedMeshSceneNode(App::getSingleton()->getGraphicEngine()->getSceneManager()->getMesh((constants::PATH_TO_MEDIA + "/projectiles/" + modelFile.C_String() + "/" + modelFile.C_String() + ".3DS").c_str()));
	m_Model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	m_Model->setPosition(m_Owner->GetPlane()->getPosition());
	m_Model->setRotation(m_Owner->GetPlane()->getRotation());
}