#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <irrlicht.h>

#include "NetworkIDManager.h"

class Player;

class Faction : public RakNet::NetworkIDObject
{
public:
	
	Faction(std::string name, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID);

	std::string GetName();

	void AddPlayer(Player* player);
	void RemovePlayer(Player* player);

	bool HasPlayer(Player* player);

	std::vector<Player*> GetPlayers();

	irr::core::vector3df GetPosition();
	irr::core::vector3df GetRotation();

private:
	
	std::string m_Name;

	std::vector<Player*> m_Players;
	
	irr::core::vector3df m_Position;
	irr::core::vector3df m_Rotation;
};