#pragma once

#include <string>

#include <irrlicht.h>

#include "NetworkIDManager.h"
#include "RakString.h"

class Faction;
class Plane;

class Player : public RakNet::NetworkIDObject
{
private:

	std::string nickname;

	Faction* m_Faction;

	Plane* plane;

	irr::scene::ICameraSceneNode* m_Camera;

	//Seul le network devra modifier ces vars: 
	int score;
	int cash;
	int kills;
	int deaths;
	int ping;

public:
	
	Player(RakNet::RakString nick, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID);
	~Player();
	
	Faction* GetFaction();
	void SetFaction(Faction* faction);

	Plane* GetPlane();
	void SetPlane(RakNet::RakString name);

	irr::scene::ICameraSceneNode* GetCamera();
	void SetCamera();

	void updateThirdView();

	//// GETTERS AND SETTERS //// 
	
	void setNickname(std::string name);
	std::string getNickname();

	void setScore(int score);
	int getScore();

	void setCash(int cash);
	int getCash();

	void setKills(int kills);
	int getKills();

	void setDeaths(int deaths);
	int getDeaths();

	void setPing(int ping);
	int getPing();
};