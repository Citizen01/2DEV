#include "particle_emitter.h"
#include "particle_manager.h"
#include "app.h"
#include <ctime>

using namespace irr;

particle_emitter::particle_emitter(
		constants::PARTICLE_TYPE type,
		irr::core::vector3df position,
		irr::core::vector3df rotation,
		irr::core::vector3df scale
		)
{
	particle_node = App::getSingleton()->getGraphicEngine()->getSceneManager()->addParticleSystemSceneNode(false);
	video::IVideoDriver* driver = App::getSingleton()->getGraphicEngine()->getDriver();
		
	switch (type)
	{
	case constants::PARTICLE_FIRE_NORMAL:
		//TODO:
		break;
	case constants::PARTICLE_FIRE_DIRECTED:
		//TODO:
		break;
	case constants::PARTICLE_EXPLOSION: 
		{
			emitter = particle_node->createBoxEmitter(
			core::aabbox3d<f32>(0.1,0.1,0.1,0.1,0.1,0.1), // emitter size
			core::vector3df(0.01f,0.01f,0.01f),   // initial direction
			500,500,                             // emit rate
			video::SColor(0,255,255,255),       // darkest color
			video::SColor(0,255,255,255),       // brightest color
			1000,1000,360,                         // min and max age, angle
			core::dimension2df(6.f,6.f),         // min size
			core::dimension2df(6.f,6.f));        // max size
			particle_node->setEmitter(emitter); // this grabs the emitter
			emitter->drop(); // so we can drop it here without deleting it
			scene::IParticleAffector* paf = particle_node->createFadeOutParticleAffector();
			particle_node->addAffector(paf); // same goes for the affector
			paf->drop();
			particle_node->setPosition(position);
			particle_node->setMaterialFlag(video::EMF_LIGHTING, false);
			particle_node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
			particle_node->setMaterialTexture(0, driver->getTexture("../Media/test/fire.bmp"));
			particle_node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

			remainingTime = 200; //200 ms
		}
		break;
	case constants::PARTICLE_SMOKE_WHITE:
		//TODO:
		break;
	case constants::PARTICLE_SMOKE_BLACK:
		//TODO:
		break;
	case constants::PARTICLE_LIGHT_WHITE:
		//TODO:
		break;
	case constants::PARTICLE_TYPE_COUNT:
		//TODO:
		break;
	default:
		break;
	}

	attachedTo = NULL;
	lastUpdate = clock();
}


particle_emitter::~particle_emitter(void)
{
}


void particle_emitter::attachTo(irr::scene::ISceneNode* node)
{
	if (node != NULL)
		attachedTo = node;
}

void particle_emitter::detach()
{
	attachedTo = NULL;
}

void particle_emitter::update()
{
	//On décrémente le remainingTime
	if (remainingTime > 0)
	{
		clock_t c_delta = clock() - lastUpdate;
		float delta = (((float)c_delta)/CLOCKS_PER_SEC);
		remainingTime -= delta*1000;
		lastUpdate = clock();
	}
	else
	{
		stop();
		return;
	}

	//On met à jour la position du node
	if (particle_node!= NULL && attachedTo != NULL)
		particle_node->setPosition(attachedTo->getPosition());
}

void particle_emitter::stop()
{
	particle_node->getEmitter()->setMaxParticlesPerSecond(0);
	particle_node->getEmitter()->setMinParticlesPerSecond(0);
	
	//Déréférencement:
	particle_manager::getSingleton()->removeParticleEmitter(this);
}