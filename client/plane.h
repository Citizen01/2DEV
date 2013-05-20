#pragma once

#include <string>
#include <irrlicht.h>
#include "app.h"

using namespace irr;

class Plane
{

private:
	App* _app; //Objet game auquel il fait partit
	std::string _name; //nom du model de l'avion
	scene::IAnimatedMeshSceneNode* _model;
	core::vector3df _position;
	core::vector3df _rotation;
	
public:
	Plane(App* app, std::string);
	~Plane(void);

	void loadMesh();

	//// GETTERS ////
	inline std::string getName() { return _name; }
	inline scene::IAnimatedMeshSceneNode* getMesh() { return _model; }
	inline core::vector3df getPosition() { return _position; }
	inline core::vector3df getRotation() { return _rotation; }

	//// SETTERS ////

};

