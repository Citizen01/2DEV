#pragma once

#include <irrlicht.h>
#include <vector>
#include <map>

class particle_manager
{
private:

	//R�f�rence tous les IParticleSystemSceneNode*
	std::vector<irr::scene::IParticleSystemSceneNode*> particle_nodes;

	//Associe un IParticleSystemSceneNode* � un IAnimatedMeshSceneNode*
	std::map<irr::scene::IParticleSystemSceneNode*, irr::scene::IAnimatedMeshSceneNode*> relationships;

public:
	particle_manager(void);
	~particle_manager(void);

	void attachParticlesTo(

};
