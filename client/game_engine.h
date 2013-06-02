#pragma once

#include "engine.h"

#include "plane.h"

class engine;

class game_engine : public engine
{
public:
	game_engine();
	~game_engine(void);

	Plane* joueur; //TODO: a bouger dans game (remove include)

	void frame();

	// Fonction qui récupère tous les events
	bool OnEvent(const irr::SEvent& event);

	//TODO: A supprimer après le passage de Plane* joueur dans game
	void setPlane(Plane* pl);

};

