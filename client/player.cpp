#include "player.h"

using namespace std;
using namespace irr;

Player::Player(string n)
{
	name = n;
	score = 0;
	kills = 0;
	deaths = 0;
	ping = 0;
}


Player::~Player(void)
{
	delete plane;
}

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