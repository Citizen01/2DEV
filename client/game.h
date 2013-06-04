#pragma once

#include "player.h"
#include "map.h"
#include "GLOBALS.h"
#include <vector>

class game
{
private:
	Map* map;
	GameRules rules;
	std::vector<Player*> player_list;

	//Assigné automatiquement lors du 1er appel à getLocalPlayer()
	Player* local_player;

public:
	game(void);
	~game(void);

	Player* addLocalPlayer();
	Player* addPlayer(std::string nickname);

	Player* getLocalPlayer();
	Player* getPlayerByName(std::string nickname);
	std::vector<Player*> getPlayerList();

	bool removePlayer(Player* p);
};

