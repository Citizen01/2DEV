#pragma once

#include "engine.h"
class graphics_engine : public engine
{
public:
	graphics_engine(Game*);
	~graphics_engine(void);

	void frame();
};

