#include "sound_engine.h"
#include "GLOBALS.h"
#include <iostream>
#include "app.h"

using namespace std;
using namespace constants;


sound_engine::sound_engine(App* a) : engine(a)
{
	// start irrKlang with default parameters
	soundEngine = irrklang::createIrrKlangDevice();
	soundEndEvent = new MySoundEndReceiver();
	ready = false;
}

sound_engine::~sound_engine(void)
{
	soundEngine->stopAllSounds();
	soundEngine->drop(); // delete irrklang engine
}

void sound_engine::playClick() 
{
	play2D("click.mp3");
}

/*
* définit la musique actuelle
*/
void sound_engine::playBackgroundMusic(std::string name)
{
	backgroundMusic = soundEngine->play2D((PATH_TO_MEDIA + "/sounds/" + name).c_str(), true, false, true);
}

/*
* stoppe et clean la background music
*/
void sound_engine::stopBackgroundMusic()
{
	if(backgroundMusic) {
		backgroundMusic->stop();
		backgroundMusic->drop();
	}
}

/*
* pause la background music
*/
void sound_engine::setPauseBackgroundMusic(bool pause)
{
	if(pause) {
		backgroundMusic->setIsPaused(true);
	} else {
		backgroundMusic->setIsPaused(false);
	}
}

/*
* Joue un simple son 2D
*/
void sound_engine::play2D(std::string name)
{
	irrklang::ISound* sound = soundEngine->play2D((PATH_TO_MEDIA + "/sounds/" + name).c_str(), false, false, true);
	sound->setSoundStopEventReceiver(soundEndEvent);
}

/*
*	Joue un son 3D a une position précisée
*   Prend en paramétre le nom du fichier son (machin.mp3), la position a utiliser, la distance maximum (Entre cette distance et la distance minimum, le son augmente) et la distance minimum (Entre 0 et cette distance, le son n'augmente pas)
*/
void sound_engine::play3D(std::string name, core::vector3df position, float minDistance, float maxDistance)
{
	irrklang::vec3df vector = irrklang::vec3df();
	irrklang::ISound* sound = soundEngine->play3D((PATH_TO_MEDIA + "/sounds/" + name).c_str(),irrklang::vec3df(position.X, position.Y, position.Z),false,false,true);
	sound->setMinDistance(minDistance);
	sound->setMaxDistance(maxDistance);
	sound->setSoundStopEventReceiver(soundEndEvent);
}

/*
*	Attache un son 3D a un IAnimatedMeshSceneNode
*   Prend en paramétre le nom du fichier son (machin.mp3), le SceneNode a lier, la distance maximum (Entre cette distance et la distance minimum, le son augmente) et la distance minimum (Entre 0 et cette distance, le son n'augmente pas)
*/
void sound_engine::attach3DSound(std::string name, scene::IAnimatedMeshSceneNode* modele, float minDistance, float maxDistance, bool looped)
{
	int size = soundMap3D[modele].size();
	int counter = 0;
	bool exists = false;

	//Check if this sound is already attached to this SceneNode
	for(counter = 0; counter < size; counter ++) {
		irrklang::ISoundSource* source = soundMap3D[modele][counter]->getSoundSource();
		if(source->getName() ==  (PATH_TO_MEDIA + "/sounds/" + name)) {
			exists = true;
		}
	}

	if(!exists) {
		core::vector3df position = modele->getAbsolutePosition();
		irrklang::ISound* sound = soundEngine->play3D((PATH_TO_MEDIA + "/sounds/" + name).c_str(),irrklang::vec3df(position.X, position.Y, position.Z),looped,false,true);
		sound->setMinDistance(minDistance);
		sound->setMaxDistance(maxDistance);
		//TODO: Create an ISoundStopEventReceiver class and use id
		//sound->setSoundStopEventReceiver();
		soundMap3D[modele].push_back(sound);
	}
}

/*
* Met à jour le listener de l'engine avec la position et la direction de la camera
*/
void sound_engine::updateListenerPosition(core::vector3df position, core::vector3df direction)
{
	soundEngine->setListenerPosition(irrklang::vec3df(position.X, position.Y, position.Z),irrklang::vec3df(direction.X, direction.Y, direction.Z));
}

/*
* Gestion des évènements
*/
bool sound_engine::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	return false;
}

/*
* Apellée a chaque frame, permet d'update la position de chaque son 3d attaché a un sceneNode
*/
void sound_engine::frame()
{
	if (ready)
	{
		scene::ICameraSceneNode* camera = App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetCamera();
		if (camera)
			updateListenerPosition(camera->getAbsolutePosition(),camera->getTarget());
	}


	int innerCounter = 0;
	for (std::map<scene::IAnimatedMeshSceneNode*, std::vector<irrklang::ISound*>>::iterator it = soundMap3D.begin(); it != soundMap3D.end(); ++it)
	{
		scene::IAnimatedMeshSceneNode* modele = it->first;
		core::vector3df position = modele->getAbsolutePosition();

		std::vector<irrklang::ISound*> tempSoundVector = it->second;
		std::vector<int> indexes;
		for(unsigned int counter = 0; counter < tempSoundVector.size(); counter ++) {
			if(tempSoundVector[counter]->isFinished()) {
				tempSoundVector[counter]->drop();
				indexes.push_back(counter);
			} else {
				tempSoundVector[counter]->setPosition(irrklang::vec3df(position.X, position.Y, position.Z));
			}
		}

		for(unsigned int i = 0; i < indexes.size(); i ++) {
			tempSoundVector.erase(tempSoundVector.begin() + indexes[i]);
		}
	}
}


/*
*	Drop du isound* quand le son s'est arrêté
*/
void sound_engine::MySoundEndReceiver::OnSoundStopped (irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData)
{
	sound->drop();
}

void sound_engine::setAsReady()
{
	ready = true;
}