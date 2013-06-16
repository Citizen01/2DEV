#include "player.h"

#include "faction.h"
#include "plane.h"

using namespace std;
using namespace irr;
using namespace RakNet;

Player::Player(RakString nick, RakNet::NetworkIDManager* networkIDManager)
{
	m_Nickname = nick.C_String();

	m_Faction = NULL;
	m_Plane = NULL;

	this->SetNetworkIDManager(networkIDManager);
	this->GetNetworkID();
}

Player::~Player(void)
{
	delete m_Plane;
}

void Player::setPlane(RakString name)
{
	m_Plane = new Plane(this, name.C_String());
}