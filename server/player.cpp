#include "player.h"

#include "faction.h"
#include "plane.h"

using namespace std;
using namespace irr;
using namespace RakNet;

Player::Player(RakString nick, RakNet::NetworkIDManager* networkIDManager)
{
	nickname = nick.C_String();

	m_Faction = NULL;
	plane = NULL;

	score = 0;
	cash = 0;
	kills = 0;
	deaths = 0;
	ping = 0;

	this->SetNetworkIDManager(networkIDManager);
	this->GetNetworkID();
}

Player::~Player(void)
{
	delete plane;
}

Faction* Player::GetFaction()
{
	return m_Faction;
}

void Player::SetFaction(Faction* faction)
{
	m_Faction = faction;
}

Plane* Player::GetPlane()
{
	return plane;
}

void Player::SetPlane(RakString name, scene::ISceneManager* sceneManager)
{
	plane = new Plane(this, name.C_String(), sceneManager);
}

void Player::updateThirdView()
{
}

///////////////// GETTERS AND SETTERS /////////////////

//Name

std::string Player::getNickname()
{
	return nickname;
}

RakString Player::GetRakName()
{
	return RakString(nickname.c_str());
}

//Score
void Player::setScore(int score)
{
	if (score >= 0)
		this->score = score;
	else
		score = 0;
}


int Player::getScore()
{
	return score;
}

//Cash
void Player::setCash(int score)
{
	this->cash = cash;
}


int Player::getCash()
{
	return cash;
}

//Kills
void Player::setKills(int kills)
{
	if (kills >= 0)
		this->kills = kills;
	else
		kills = 0;
}

int Player::getKills()
{
	return kills;
}

//Deaths
void Player::setDeaths(int deaths)
{
	if (deaths >= 0)
		this->deaths = deaths;
	else
		deaths = 0;
}

int Player::getDeaths()
{
	return deaths;
}

//Ping
void Player::setPing(int ping)
{
	if (ping >= 0)
		this->ping = ping;
	else
		ping = 0;
}

int Player::getPing()
{
	return ping;
}
///////////////////////////////////////////////////////
