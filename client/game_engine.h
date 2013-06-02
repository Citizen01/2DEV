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

	// Fonction qui r�cup�re tous les events
	bool OnEvent(const irr::SEvent& event);

	//TODO: A supprimer apr�s le passage de Plane* joueur dans game
	void setPlane(Plane* pl);

};

