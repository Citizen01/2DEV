#pragma once

#include <irrlicht.h>
#include <ctime>
#include "GLOBALS.h"

class particle_emitter
{
private:
	irr::scene::IParticleSystemSceneNode* particle_node;
	irr::scene::IParticleEmitter* emitter;

	//Temps restant avant auto-suppression
	float remainingTime;
	clock_t lastUpdate;

	irr::scene::ISceneNode* attachedTo;

public:
	particle_emitter(
		constants::PARTICLE_TYPE,
		irr::core::vector3df position,
		irr::core::vector3df rotation = irr::core::vector3df(0.f, 0.f, 0.f),
		irr::core::vector3df scale = irr::core::vector3df(1.f, 1.f, 1.f)
		);
	~particle_emitter(void);

	//Permet au particle_emitter de s'attacher � un ISceneNode.
	void attachTo(irr::scene::ISceneNode* node);

	//Permer au particle_emitter de se d�tacher
	void detach();

	//Met � jour sa dur�e de vie s'il en � une, ainsi que sa position si attach� � un ISceneNode
	void update();

	//Stop l'emmission de nouvelles particules
	void stop();

};

