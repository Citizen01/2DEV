#pragma once

#include <string>
#include <irrlicht.h>
#include "game.h"

using namespace irr;

class Plane
{

private:
	game* _game; //Objet game auquel il fait partit
	std::string _name; //nom du model de l'avion
	scene::IAnimatedMesh* _model;
	core::vector3df _position;
	core::vector3df _rotation;
	
public:
	Plane(game* g, std::string);
	~Plane(void);

	void loadMesh();

	//// GETTERS ////
	inline std::string getName() { return _name; }
	inline scene::IAnimatedMesh* getMesh() { return _model; }
	inline core::vector3df getPosition() { return _position; }
	inline core::vector3df getRotation() { return _rotation; }

	//// SETTERS ////

};

