#pragma once

#include <irrlicht.h>

class game_engine;
class graphics_engine;
class network_engine;
class sound_engine;
class Application;

class engine : public irr::IEventReceiver
{
public:
	//Partie du constructeur commune � tous les moteurs
	engine(Application* ap);
	virtual ~engine();

	//M�thodes permettant le linkage avec les autres modules
	void link_game_engine(game_engine*);
	void link_graphics_engine(graphics_engine*);
	void link_network_engine(network_engine*);
	void link_sound_engine(sound_engine*);

	//M�thode qui sera impl�ment� dans les classes filles
	//Elle contiendra les actions propres � chaque moteur
	virtual void frame() = 0;

	//H�rit� de la classe IEventReceiver
	virtual bool OnEvent(const irr::SEvent& event) = 0;


protected:
	//Contiendra l'objet Application instanci�
	Application* parent;

	//R�f�rencement de tous les moteurs
	game_engine *ge;
	network_engine *ne;
	graphics_engine *gfxe;
	sound_engine *se;

};

