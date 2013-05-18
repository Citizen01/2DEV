#pragma once

#include "application.h"
#include <irrlicht.h>

class MainEventListener : public irr::IEventReceiver
{
private:
	Application* app;

public:
	MainEventListener(Application* ap);
	~MainEventListener(void);

	/* Méthode qui réceptionne tous les events (clavier/souris)
	   et les propage aux event receivers interessés */
	virtual bool OnEvent(const irr::SEvent& event);
	
};

