#pragma once

#include "engine.h"

class engine;

class network_engine : public engine
{
public:
	network_engine(Application* ap);
	~network_engine(void);

	void frame();

	// Fonction qui r�cup�re tous les events
	bool OnEvent(const irr::SEvent& event);
};

