#pragma once

#include "engine.h"
#include <irrKlang.h>
#include "game.h"
#include <map>
#include <vector>
#include <iostream>

using namespace irr;

class engine;

class sound_engine : public engine
{
private:
	irrklang::ISoundEngine* soundEngine;
	std::map<scene::IAnimatedMeshSceneNode*, std::vector<irrklang::ISound*>> soundMap3D;
	std::vector<irrklang::ISound*> soundVector2D;

public:
	sound_engine(App* a);
	~sound_engine(void);

	void play2D(std::string name);
	void play3D(std::string name, core::vector3df position, float minDistance, float maxDistance);
	void attach3DSound(std::string name, irr::scene::IAnimatedMeshSceneNode* node, float minDistance, float maxDistance);

	void updateListenerPosition(core::vector3df position, core::vector3df direction);

	void frame();

	// Fonction qui récupère tous les events
	bool OnEvent(const irr::SEvent& event);
};