#pragma once

#include "engine.h"
class network_engine : public engine
{
public:
	network_engine(Game*);
	~network_engine(void);

	void frame();
};

