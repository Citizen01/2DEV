#pragma once

#include <vector>

#include "RakString.h"

#include "GLOBALS.h"

#include "map.h"
#include "faction.h"
#include "player.h"

class Projectile;

class game
{
private:

	Map* map;

	GameRules rules;

	std::vector<Faction*> faction_list;
	std::vector<Player*> player_list;
	std::vector<Projectile*> projectile_list;

	//Assigné automatiquement lors du 1er appel à getLocalPlayer()
	Player* local_player;

public:

	game(std::string mapName);
	~game(void);

	void addPlayer(RakNet::RakString playerName, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID);
	bool removePlayer(Player* p);
	
	void addFaction(std::string factionName, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID, int maxPlayers);

	void addProjectile(Player* owner, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID, RakNet::RakString modelFile);

	Player* getLocalPlayer();
	Player* getPlayerByName(std::string nickname);

	std::vector<Player*> getPlayerList();
	std::vector<Faction*> getFactionList();

	void updateJoinFactionWindow();

};

