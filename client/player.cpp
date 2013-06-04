#include "player.h"

using namespace std;
using namespace irr;

Player::Player(string nick)
{
	is_local_player = false;
	nickname = nick;
	score = 0;
	cash = 0;
	kills = 0;
	deaths = 0;
	ping = 0;
}

Player::Player(string nick, bool is_local)
{
	Player::Player(nick); //Appel le constructeur par defaut
	is_local_player = is_local; //Remplace la valeur par defaut par celle de is_local
}

Player::~Player(void)
{
	delete plane;
}

bool Player::isLocalPlayer()
{
	return is_local_player;
}

///////////////// GETTERS AND SETTERS /////////////////

//Position
void Player::setPosition(core::vector3df position)
{
	if (plane != NULL)
		plane->getMesh()->setPosition(position);
}

core::vector3df Player::getPosition()
{
	if (plane != NULL)
		return plane->getMesh()->getPosition();
	else
		return core::vector3df(NULL, NULL, NULL);
}

//Rotation
void Player::setRotation(core::vector3df rotation)
{
	if (plane != NULL)
		plane->getMesh()->setRotation(rotation);
}

core::vector3df Player::getRotation()
{
	if (plane != NULL)
		return plane->getMesh()->getRotation();
	else
		return core::vector3df(NULL, NULL, NULL);
}

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
