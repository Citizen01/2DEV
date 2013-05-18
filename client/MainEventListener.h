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

	/* M�thode qui r�ceptionne tous les events (clavier/souris)
	   et les propage aux event receivers interess�s */
	virtual bool OnEvent(const irr::SEvent& event);
	
};

