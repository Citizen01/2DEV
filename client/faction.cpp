#include "faction.h"
#include "app.h"
#include "player.h"

using namespace std;
using namespace RakNet;
using namespace irr;

Faction::Faction(std::string name, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID, int maxPlayers)
{
	m_Name = name;

	vector<Player*> m_Players;

	this->SetNetworkIDManager(networkIDManager);
	this->SetNetworkID(networkID);
	
	m_Position = core::vector3df(50000, 19997, 50015);
	m_Rotation = core::vector3df(0.f, 0.f, 0.f);

	m_MaxPlayers = maxPlayers;
}

string Faction::GetName()
{
	return m_Name;
}

void Faction::AddPlayer(Player* player)
{
	player->SetFaction(this);
	m_Players.push_back(player);
	App::getSingleton()->getGameEngine()->GetGame()->updateJoinFactionWindow();
}

void Faction::RemovePlayer(Player* player)
{
	for (unsigned int i = 0; i < m_Players.size(); i++)
	{
		Player* p = m_Players[i];
		if (player == p)
		{
			player->SetFaction(NULL);
			m_Players.erase(m_Players.begin() + i);
			break;
		}
	}
}

bool Faction::HasPlayer(Player* player)
{
	for (unsigned int i = 0; i < m_Players.size(); i++)
	{
		Player* p = m_Players[i];
		if (player == p)
		{
			return true;
		}
	}
	return false;
}

vector<Player*> Faction::GetPlayers()
{
	return m_Players;
}

irr::core::vector3df Faction::GetPosition()
{
	return m_Position;
}

irr::core::vector3df Faction::GetRotation()
{
	return m_Rotation;
}