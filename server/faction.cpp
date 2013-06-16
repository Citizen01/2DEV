#include "faction.h"

#include "player.h"

using namespace std;
using namespace RakNet;
using namespace irr;

Faction::Faction(std::string name, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID)
{
	m_Name = name;

	vector<Player*> m_Players;

	this->SetNetworkIDManager(networkIDManager);
	this->SetNetworkID(networkID);
	
	m_Position = core::vector3df(0, 10, 0);
	m_Rotation = core::vector3df(-90.f, 0.f, 0.f);
	m_MaxPlayers = 3;
}

string Faction::getName()
{
	return m_Name;
}

RakString Faction::getRakName()
{
	return RakString(m_Name.c_str());
}

void Faction::addPlayer(Player* player)
{
	player->setFaction(this);
	m_Players.push_back(player);
}

void Faction::removePlayer(Player* player)
{
	for (unsigned int i = 0; i < m_Players.size(); i++)
	{
		if (player == m_Players[i])
		{
			player->setFaction(NULL);
			m_Players.erase(m_Players.begin() + i);
			break;
		}
	}
}

bool Faction::hasPlayer(Player* player)
{
	for (unsigned int i = 0; i < m_Players.size(); i++)
	{
		if (player == m_Players[i])
		{
			return true;
		}
	}
	return false;
}

vector<Player*> Faction::getPlayers()
{
	return m_Players;
}

irr::core::vector3df Faction::getPosition()
{
	return m_Position;
}

irr::core::vector3df Faction::getRotation()
{
	return m_Rotation;
}