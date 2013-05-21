#pragma once

#include "engine.h"

class engine;
class App;
class Plane;

class game_engine : public engine
{
public:
	game_engine();
	~game_engine(void);

	Plane* joueur;

	void frame();

	// Fonction qui r�cup�re tous les events
	bool OnEvent(const irr::SEvent& event);

};

