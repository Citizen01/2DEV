#pragma once

#include "game.h"
#include <irrlicht.h>

class MainEventListener : public irr::IEventReceiver
{
private:
	game* g;

public:
	MainEventListener(game* ga);
	~MainEventListener(void);

	/* Méthode qui réceptionne tous les events (clavier/souris)
	   et les propage aux event receivers interessés */
	virtual bool OnEvent(const irr::SEvent& event);
	
};

