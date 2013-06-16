#include "particle_manager.h"

particle_manager* particle_manager::instance = NULL;

particle_manager::particle_manager(void)
{
}

particle_manager::~particle_manager(void)
{
	for (unsigned int i = 0; i < partEmitters.size(); i++)
		delete partEmitters[i];
}

particle_manager* particle_manager::getSingleton()
{
	if (!instance)
		instance = new particle_manager();

	return instance;
}

void particle_manager::createParticleEmitter(
		constants::PARTICLE_TYPE type,
		irr::core::vector3df position,
		irr::core::vector3df rotation,
		irr::core::vector3df scale
		)
{
	particle_emitter* part = new particle_emitter(type, position, rotation, scale);
	partEmitters.push_back(part);
}

void particle_manager::updateAll()
{
	for (unsigned int i = 0; i < partEmitters.size(); i++)
		partEmitters[i]->update();
}

void particle_manager::removeParticleEmitter(particle_emitter* pem)
{
	unsigned int i = 0;
	for (i = 0; i < partEmitters.size(); i++)
		if (partEmitters[i] == pem)
			break;
	partEmitters.erase(partEmitters.begin()+i);
}