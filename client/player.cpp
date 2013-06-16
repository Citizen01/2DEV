#include "player.h"

#include "app.h"
#include "faction.h"
#include "plane.h"

using namespace std;
using namespace irr;
using namespace RakNet;

Player::Player(RakString nick, RakNet::NetworkIDManager* networkIDManager, RakNet::NetworkID networkID)
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
	this->SetNetworkID(networkID);
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

void Player::SetPlane(RakString name)
{
	plane = new Plane(this, name.C_String());
	if(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer() == this)
	{
		updateThirdView();
	}
}

void Player::SetCamera()
{
	m_Camera = App::getSingleton()->getGraphicEngine()->getSceneManager()->addCameraSceneNode(0, core::vector3df(0,0,0), core::vector3df(1,0,0));
	m_Camera->setPosition(core::vector3df(50000,20000,50000));
	m_Camera->setFarValue(420000.0f);
}

scene::ICameraSceneNode* Player::GetCamera()
{
	return m_Camera;
}

void Player::updateThirdView()
{
	//get rotation matrix of node
	core::matrix4 m;
	m.setRotationDegrees(plane->getRotation());
   
	// transform forward vector of camera
	core::vector3df frv = core::vector3df (0.0f, 0.0f, 1.0f);
	m.transformVect(frv);
   
	// transform upvector of camera
	core::vector3df upv = core::vector3df (0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	// transform camera offset
	core::vector3df offset = core::vector3df(0, 2, -15);

	m.transformVect(offset);
   
	// set camera
	m_Camera->setPosition(plane->getPosition() + offset); //position camera in front of the ship
	m_Camera->setUpVector(upv); //set up vector of camera
	m_Camera->setTarget(plane->getPosition() + frv); //set target of camera (look at point)
	App::getSingleton()->getSoundEngine()->setAsReady();
}

///////////////// GETTERS AND SETTERS /////////////////

//Name
void Player::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

std::string Player::getNickname()
{
	return nickname;
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
