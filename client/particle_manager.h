#pragma once

#include "particle_emitter.h"
#include <irrlicht.h>
#include <vector>

class particle_manager
{
private:
	static particle_manager* instance;
	particle_manager(void);

	//Référence tous les IParticleSystemSceneNode*
	std::vector<particle_emitter*> partEmitters;


public:
	static particle_manager* getSingleton();
	~particle_manager(void);

	void createParticleEmitter(
		constants::PARTICLE_TYPE,
		irr::core::vector3df position,
		irr::core::vector3df rotation = irr::core::vector3df(0.f, 0.f, 0.f),
		irr::core::vector3df scale = irr::core::vector3df(1.f, 1.f, 1.f)
		);

	//Met à jour tous les particle emitters
	void updateAll();

	void removeParticleEmitter(particle_emitter* pem);

};
