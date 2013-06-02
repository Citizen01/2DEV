/**
 * Classe qui va recevoir tous les events et les r�plicer aux engines.
 */

#pragma once

#include <irrlicht.h>

class MainEventListener : public irr::IEventReceiver
{
public:
	MainEventListener();
	~MainEventListener(void);

	/* M�thode qui r�ceptionne tous les events (clavier/souris)
	 * et les propage aux event receivers interess�s.
	 */
	virtual bool OnEvent(const irr::SEvent& event);

	/*
	 * M�thode qui trigger un constants::ACTION si la touche bind�e
	 * � cette action est press�e.
	 */
	void MainEventListener::listenForBindedKeys(const irr::SEvent& e);
	
};

