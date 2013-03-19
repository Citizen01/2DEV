#pragma once

#include <string>
#include <irrlicht.h>

using namespace irr;

class Plane
{

private:
	std::string name;
	int health;
	int maxHealth;
	scene::IAnimatedMesh* model;
	core::vector3df position;
	core::vector3df rotation;
	
public:
	Plane(void);
	~Plane(void);

};

