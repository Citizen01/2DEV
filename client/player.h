#pragma once

#include <string>
#include "plane.h"

class Player
{
private:
	Plane* plane;
	std::string name;

	//Seul le network devra modifier ces vars: 
	int score;
	int kills;
	int deaths;
	int ping;

public:
	Player(std::string);
	~Player();

	void setPosition(irr::core::vector3df position);
	irr::core::vector3df getPosition();

	void setRotation(irr::core::vector3df rotation);
	irr::core::vector3df getRotation(); 

};