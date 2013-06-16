#pragma once

#include <irrlicht.h>

class collidableObject
{
public:
	
	virtual irr::scene::ISceneNode* getNode() = 0;

	int objectType;
};