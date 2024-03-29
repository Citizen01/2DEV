#include "game.h"
#include "app.h"

using namespace std;
using namespace RakNet;

game::game(string mapName)
{
	map = new Map(mapName);
	local_player = NULL;
}

game::~game(void)
{
	delete map;
}

void game::addPlayer(RakString playerName, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID)
{
	player_list.push_back(new Player(playerName, networkIDManager, networkID));
	if(playerName.C_String() == App::getSingleton()->settings["nickname"])
	{
		local_player = getPlayerByName(playerName.C_String());
		local_player->SetCamera();
	}
}

bool game::removePlayer(Player* p)
{
	int pos_to_remove = NULL;
	for (unsigned int i = 0; i < player_list.size(); i++)
	{
		Player* player = player_list[i];
		if (player == p)
		{
			pos_to_remove = i;
			break;
		}
	}
	if (pos_to_remove != NULL)
	{
		player_list.erase(player_list.begin()+pos_to_remove);
		return true;
	} 
	else
	{
		return false;
	}
}

void game::addFaction(std::string factionName, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID)
{
	faction_list.push_back(new Faction(factionName, networkIDManager, networkID));
}

Player* game::getLocalPlayer()
{
	return local_player;
}

Player* game::getPlayerByName(string nickname)
{
	for each (Player* player in player_list)
	{
		if (player->getNickname() == nickname)
			return player;
	}
	return NULL;
}

std::vector<Player*> game::getPlayerList()
{
	return player_list;
}

std::vector<Faction*> game::getFactionList()
{
	return faction_list;
}
