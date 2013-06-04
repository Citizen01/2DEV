#pragma once

#include <string>
#include "plane.h"

class Player
{
private:
	bool is_local_player;
	std::string nickname;
	Plane* plane;

	//Seul le network devra modifier ces vars: 
	int score;
	int cash;
	int kills;
	int deaths;
	int ping;

public:
	Player(std::string nick);
	Player(std::string nick, bool is_local);
	~Player();

	bool isLocalPlayer();


	//// GETTERS AND SETTERS ////
	void setPosition(irr::core::vector3df position);
	irr::core::vector3df getPosition();

	void setRotation(irr::core::vector3df rotation);
	irr::core::vector3df getRotation(); 
	
	void setNickname(std::string name);
	std::string getNickname();

	void setScore(int score);
	int getScore();

	void setCash(int cash);
	int getCash();

	void setKills(int kills);
	int getKills();

	void setDeaths(int deaths);
	int getDeaths();

	void setPing(int ping);
	int getPing();
};