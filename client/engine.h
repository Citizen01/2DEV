#pragma once

#include "game.h"

class engine
{
public:
	//Partie du constructeur commune à tous les moteurs
	engine(Game*);
	virtual ~engine();

	//Méthodes permettant le linkage avec les autres modules
	void link_game_engine(game_engine*);
	void link_graphics_engine(graphics_engine*);
	void link_network_engine(network_engine*);
	void link_sound_engine(sound_engine*);

	//Méthode qui sera implémenté dans les classes filles
	//Elle contiendra les actions propres à chaque moteur
	virtual void frame() = 0;

protected:
	//Contiendra l'objet Game instancié
	Game* parent;

	//Référencement de tous les moteurs
	game_engine *ge;
	network_engine *ne;
	graphics_engine *gfxe;
	sound_engine *se;

};

