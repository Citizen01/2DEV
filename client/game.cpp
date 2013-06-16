#include "game.h"

#include "app.h"
#include "ui_windows.h"
#include "projectile.h"
#include "utils.h"

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

void game::addPlayer(RakString playerName, NetworkIDManager* networkIDManager, NetworkID networkID)
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


void game::addFaction(string factionName, NetworkIDManager* networkIDManager, NetworkID networkID, int maxPlayers)
{
	faction_list.push_back(new Faction(factionName, networkIDManager, networkID, maxPlayers));
	updateJoinFactionWindow();
}

void game::addProjectile(Player* owner, RakNet::NetworkIDManager* networkIDManager, NetworkID networkID, RakString modelFile)
{
	projectile_list.push_back(new Projectile(owner, networkIDManager, networkID, modelFile));
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

void game::updateJoinFactionWindow()
{
	vector<vector<string>> datas;
	for (unsigned int i=0; i < faction_list.size(); i++)
	{
		Faction* faction = faction_list.at(i);
		string factionName = faction->GetName();
		int playerCount = faction->GetPlayers().size();
		int playerMax = rules.FactionSlots;

		playerMax = 5;//TODO: Remove hack

		string population = intToString(playerCount) + "/" + intToString(playerMax);
		vector<string> tmp;
		tmp.push_back(factionName);
		tmp.push_back(population);
		datas.push_back(tmp);
	}
	update_team_selection(datas);
}
