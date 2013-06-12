#include "particle_emitter.h"


particle_emitter::particle_emitter(
		constants::PARTICLE_TYPE type,
		irr::core::vector3df position,
		irr::core::vector3df rotation = irr::core::vector3df(0.f, 0.f, 0.f),
		irr::core::vector3df scale = irr::core::vector3df(1.f, 1.f, 1.f)
		)
{
	switch (type)
	{
	case constants::FIRE_NORMAL:
		//TODO:
		break;
	case constants::FIRE_DIRECTED:
		//TODO:
		break;
	case constants::EXPLOSION:
		//TODO:
		break;
	case constants::SMOKE_WHITE:
		//TODO:
		break;
	case constants::SMOKE_BLACK:
		//TODO:
		break;
	case constants::LIGHT_WHITE:
		//TODO:
		break;
	case constants::PARTICLE_TYPE_COUNT:
		//TODO:
		break;
	default:
		break;
	}
}


particle_emitter::~particle_emitter(void)
{
	I
}
