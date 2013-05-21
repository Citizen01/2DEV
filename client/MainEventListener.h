#pragma once

#include "app.h"
#include <irrlicht.h>

class MainEventListener : public irr::IEventReceiver
{
public:
	MainEventListener();
	~MainEventListener(void);

	/* Méthode qui réceptionne tous les events (clavier/souris)
	   et les propage aux event receivers interessés */
	virtual bool OnEvent(const irr::SEvent& event);
	
};

