#pragma once

#include "engine.h"

class engine;

class network_engine : public engine
{
public:
	network_engine(game*);
	~network_engine(void);

	void frame();

	void on_engines_linked();
};

