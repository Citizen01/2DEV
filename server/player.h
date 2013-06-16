#pragma once

#include <string>

#include "NetworkIDManager.h"
#include "RakString.h"

#include <irrlicht.h>

#include "server.h"

class Faction;
class Plane;

class Player : public RakNet::NetworkIDObject
{
private:

	std::string m_Nickname;

	Faction* m_Faction;

	Plane* m_Plane;

public:
	
	Player(RakNet::RakString nickName, RakNet::NetworkIDManager* networkIDManager);
	~Player();
	
	inline std::string getNickname() { return m_Nickname; }
	inline RakNet::RakString getRakNickName() { return RakNet::RakString(m_Nickname.c_str()); }

	inline Faction* getFaction() { return m_Faction; }
	inline void setFaction(Faction* faction) { m_Faction = faction; }

	inline Plane* getPlane() { return m_Plane; }
	void setPlane(RakNet::RakString name);
};