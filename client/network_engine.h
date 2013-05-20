#pragma once

#include "engine.h"

class engine;

class network_engine : public engine
{
public:
	network_engine(App* ap);
	~network_engine(void);

	void frame();

	// Fonction qui récupère tous les events
	bool OnEvent(const irr::SEvent& event);
};

