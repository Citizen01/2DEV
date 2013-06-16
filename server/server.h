#pragma once

#include <ctime>

#include <string>
#include <iostream>
#include <vector>

#include "RakPeerInterface.h"
#include "BitStream.h"
#include "GetTime.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"  

#include "utils.h"
#include "map.h"
#include "faction.h"
#include "player.h"
#include "plane.h"

class Projectile;

class Server
{
private:

	static Server* m_Instance;

	#define MAX_CLIENTS 10
	#define SERVER_PORT 12320

	enum GameMessages
	{
			ID_ANSWER_TO_MAP = ID_USER_PACKET_ENUM,
			ID_ASK_FOR_MAP,
			ID_ASK_FOR_FACTIONS,
			ID_ANSWER_TO_FACTIONS,
			ID_ASK_FOR_PLAYERS,
			ID_ANSWER_TO_PLAYERS,
			ID_ASK_FOR_LOCAL_PLAYER,
			ID_ASK_TO_ENTER_FACTION,
			ID_PLAYER_ENTER_FACTION,
			ID_PLAYER_DO_NOT_ENTER_FACTION,
			ID_ASK_FOR_LOCAL_PLANE,
			ID_PLAYER_GET_PLANE,
			ID_ASK_FOR_PLAYERS_STATES,
			ID_ASK_FOR_PROJECTILES,
			ID_ASK_TO_ACCELERATE,
			ID_ACCELERATE_PLANE,
			ID_ASK_TO_DECELERATE,
			ID_DECELERATE_PLANE,
			ID_ASK_TO_DIVE,
			ID_DIVE_PLANE,
			ID_ASK_TO_STRAIGHTEN,
			ID_STRAIGHTEN_PLANE,
			ID_ASK_TO_ROLL_LEFT,
			ID_ROLL_LEFT_PLANE,
			ID_ASK_TO_ROLL_RIGHT,
			ID_ROLL_RIGHT_PLANE,
			ID_MOVE_PLANE,
			ID_ASK_TO_SHOOT_MISSILE,
			ID_SHOOT_MISSILE,
			ID_UPDATE_PROJECTILE,

			TOTAL_MESSAGES
	};
		
	RakNet::NetworkIDManager* m_NetworkIDManager;
	RakNet::RakPeerInterface* m_Peer;

	RakNet::SocketDescriptor m_SocketDescriptor;
	RakNet::Packet* m_Packet;

	RakNet::BitStream m_BSOut;

	std::vector<RakNet::SystemAddress> m_PlayersWhoAreReady;

	Map* m_Map;

	std::vector<Faction*> m_FactionList;
	std::vector<Player*> m_PlayerList;
	std::vector<Projectile*> m_ProjectileList;

	bool m_Running;

	clock_t m_CurrentTime;
	clock_t m_ElapsedTime;
	
	irr::IrrlichtDevice* m_Device;
	irr::scene::ISceneManager* m_SceneManager;

	Server();

public:

	static Server* getSingleton();
	~Server();

	inline irr::scene::ISceneManager* getSceneManager() { return m_SceneManager; }

	unsigned char getPacketIdentifier();
	
	void reply();
	void broadcast();
	void broadcastToPlayersWhoAreReady();
	
	void sendMap();
	void sendFactions();
	void sendPlayers();
	void sendPlayerStates();
	void sendProjectiles();

	void newPlayer();
	void newPlane();
	
	void playerEnterFaction();
	
	void acceleratePlane();
	void deceleratePlane();
	void divePlane();
	void straightenPlane();
	void rollLeftPlane();
	void rollRightPlane();
	void shootMissile();

	void movePlanes();
	void updateProjectiles(unsigned int deltatime);

	Player* getPlayerByName(RakNet::RakString nickname);

	int run();
};