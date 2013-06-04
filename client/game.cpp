#include "game.h"
#include "app.h"

using namespace std;

game::game(void)
{
	map = NULL;
	local_player = NULL;
}


game::~game(void)
{
}


Player* game::addLocalPlayer()
{
	Player* p_ptr = new Player(App::getSingleton()->settings["nickname"], true);
	player_list.push_back(p_ptr);
	return p_ptr;
}

Player* game::addPlayer(string nickname)
{
	Player* p_ptr = new Player(App::getSingleton()->settings["nickname"]);
	player_list.push_back(p_ptr);
	return p_ptr;
}

Player* game::getLocalPlayer()
{
	if (local_player != NULL)
	{
		return local_player;
	}
	else
	{
		for each (Player* player in player_list)
		{
			if (player->isLocalPlayer())
				local_player = player;
				return player;
		}
		return NULL;
	}
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