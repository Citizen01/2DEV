#pragma once

#include <irrlicht.h>
#include "GLOBALS.h"

class particle_emitter
{
private:
	irr::scene::IParticleSystemSceneNode* particle_node;
	irr::scene::IParticleEmitter* emitter;

public:
	particle_emitter(
		constants::PARTICLE_TYPE,
		irr::core::vector3df position,
		irr::core::vector3df rotation = irr::core::vector3df(0.f, 0.f, 0.f),
		irr::core::vector3df scale = irr::core::vector3df(1.f, 1.f, 1.f)
		);
	~particle_emitter(void);

};

