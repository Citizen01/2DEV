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
	class MySoundEndReceiver : public irrklang::ISoundStopEventReceiver
	{
		public:
			virtual void OnSoundStopped (irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData);
	};
	irrklang::ISoundEngine* soundEngine;
	std::map<scene::IAnimatedMeshSceneNode*, std::vector<irrklang::ISound*>> soundMap3D;
	irrklang::ISound* backgroundMusic;
	MySoundEndReceiver* soundEndEvent;

public:
	sound_engine();
	~sound_engine(void);

	void playClick();
	void playBackgroundMusic(std::string name);
	void stopBackgroundMusic();
	void setPauseBackgroundMusic(bool pause);
	void play2D(std::string name);
	void play3D(std::string name, core::vector3df position, float minDistance, float maxDistance);
	void attach3DSound(std::string name, irr::scene::IAnimatedMeshSceneNode* node, float minDistance, float maxDistance);

	void updateListenerPosition(core::vector3df position, core::vector3df direction);

	void frame();

	// Fonction qui récupère tous les events
	bool OnEvent(const irr::SEvent& event);
};