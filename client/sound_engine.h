#pragma once

#include "engine.h"

class engine;

class sound_engine : public engine
{
public:
	sound_engine();
	~sound_engine(void);

	void frame();

	// Fonction qui récupère tous les events
	bool OnEvent(const irr::SEvent& event);
};

