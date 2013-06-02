/**
 * Classe qui va recevoir tous les events et les réplicer aux engines.
 */

#pragma once

#include <irrlicht.h>

class MainEventListener : public irr::IEventReceiver
{
public:
	MainEventListener();
	~MainEventListener(void);

	/* Méthode qui réceptionne tous les events (clavier/souris)
	 * et les propage aux event receivers interessés.
	 */
	virtual bool OnEvent(const irr::SEvent& event);

	/*
	 * Méthode qui trigger un constants::ACTION si la touche bindée
	 * à cette action est pressée.
	 */
	void MainEventListener::listenForBindedKeys(const irr::SEvent& e);
	
};

