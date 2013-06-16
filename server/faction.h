#pragma once

#include <string>
#include <vector>

#include "NetworkIDManager.h"
#include "RakString.h"

#include <irrlicht.h>

class Player;

class Faction : public RakNet::NetworkIDObject
{
public:
	
	Faction(std::string name, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID);

	std::string getName();
	RakNet::RakString getRakName();

	void addPlayer(Player* player);
	void removePlayer(Player* player);

	bool hasPlayer(Player* player);

	std::vector<Player*> getPlayers();

	irr::core::vector3df getPosition();
	irr::core::vector3df getRotation();

private:
	
	std::string m_Name;

	std::vector<Player*> m_Players;
	
	irr::core::vector3df m_Position;
	irr::core::vector3df m_Rotation;
};