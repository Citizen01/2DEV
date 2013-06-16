#pragma once

#include "engine.h"

#include "game.h"

class engine;

class game_engine : public engine
{
public:

	game_engine(App* a);
	~game_engine(void);
	
	void LaunchGame(std::string mapName);
	game* GetGame();
	void StopGame();


	void frame();

	// Fonction qui récupère tous les events
	bool OnEvent(const irr::SEvent& event);

private:

	game* m_Game;
};

