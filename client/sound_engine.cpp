#include "sound_engine.h"
#include "GLOBALS.h"
#include <iostream>

using namespace std;
using namespace constants;

sound_engine::sound_engine(App* a) : engine(a)
{
	// start irrKlang with default parameters
	soundEngine = irrklang::createIrrKlangDevice();
}

sound_engine::~sound_engine(void)
{
	soundEngine->stopAllSounds();
	soundEngine->drop(); // delete engine
}

/*
* Joue un simple son 2D
*/
void sound_engine::play2D(std::string name)
{
	irrklang::ISound* sound = soundEngine->play2D((PATH_TO_MEDIA + "/sounds/" + name).c_str(), true);
	//TODO: Create an ISoundStopEventReceiver class and use id
	//sound->setSoundStopEventReceiver();
	soundVector2D.push_back(sound);
}

/*
*	Joue un son 3D a une position précisée
*   Prend en paramétre le nom du fichier son (machin.mp3), la position a utiliser, la distance maximum (Entre cette distance et la distance minimum, le son augmente) et la distance minimum (Entre 0 et cette distance, le son n'augmente pas)
*/
void sound_engine::play3D(std::string name, core::vector3df position, float minDistance, float maxDistance)
{
	irrklang::vec3df vector = irrklang::vec3df();
	irrklang::ISound* sound = soundEngine->play3D((PATH_TO_MEDIA + "/sounds/" + name).c_str(),irrklang::vec3df(position.X, position.Y, position.Z),true,false,true);
	sound->setMinDistance(minDistance);
	sound->setMaxDistance(maxDistance);
}

/*
*	Attache un son 3D a un IAnimatedMeshSceneNode
*   Prend en paramétre le nom du fichier son (machin.mp3), le SceneNode a lier, la distance maximum (Entre cette distance et la distance minimum, le son augmente) et la distance minimum (Entre 0 et cette distance, le son n'augmente pas)
*/
void sound_engine::attach3DSound(std::string name, scene::IAnimatedMeshSceneNode* modele, float minDistance, float maxDistance)
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
		irrklang::ISound* sound = soundEngine->play3D((PATH_TO_MEDIA + "/sounds/" + name).c_str(),irrklang::vec3df(position.X, position.Y, position.Z),true,false,true);
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
	int innerCounter = 0;
	for (std::map<scene::IAnimatedMeshSceneNode*, std::vector<irrklang::ISound*>>::iterator it = soundMap3D.begin(); it != soundMap3D.end(); ++it)
	{
		scene::IAnimatedMeshSceneNode* modele = it->first;
		core::vector3df position = modele->getAbsolutePosition();
		std::vector<irrklang::ISound*> vector = it->second;
		for(unsigned int counter = 0; counter < vector.size(); counter ++) {
			vector[counter]->setPosition(irrklang::vec3df(position.X, position.Y, position.Z));
		}
	}
}
