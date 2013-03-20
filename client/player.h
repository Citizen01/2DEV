#pragma once

#include <string>
#include "plane.h"

class Player
{

private:
	std::string name;
	Plane* plane;

public:
	Player(std::string);
	~Player();

};

