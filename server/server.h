#pragma once

#include <ctime>

#include <iostream>
#include <string>
#include <vector>

#include "RakPeerInterface.h"
#include "BitStream.h"
#include "GetTime.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"  

#include "utils.h"

#include "faction.h"
#include "player.h"
#include "plane.h"

class Server
{
private:

	static Server* m_Instance;

	#define MAX_CLIENTS 10
	#define SERVER_PORT 60000

	enum GameMessages
	{
		ID_ANSWER_TO_MAP = ID_USER_PACKET_ENUM,
		ID_ASK_FOR_MAP = ID_USER_PACKET_ENUM + 1,
		ID_ASK_FOR_FACTIONS = ID_USER_PACKET_ENUM + 2,
		ID_ANSWER_TO_FACTIONS = ID_USER_PACKET_ENUM + 3,
		ID_ASK_FOR_PLAYERS = ID_USER_PACKET_ENUM + 4,
		ID_ANSWER_TO_PLAYERS = ID_USER_PACKET_ENUM + 5,
		ID_ASK_FOR_LOCAL_PLAYER = ID_USER_PACKET_ENUM + 6,
		ID_ASK_TO_ENTER_FACTION = ID_USER_PACKET_ENUM + 7,
		ID_PLAYER_ENTER_FACTION = ID_USER_PACKET_ENUM + 8,
		ID_PLAYER_DO_NOT_ENTER_FACTION = ID_USER_PACKET_ENUM + 9,
		ID_ASK_FOR_LOCAL_PLANE = ID_USER_PACKET_ENUM + 10,
		ID_PLAYER_GET_PLANE = ID_USER_PACKET_ENUM + 11,
		ID_ASK_FOR_PLAYERS_STATES = ID_USER_PACKET_ENUM + 12,
		ID_ASK_TO_ACCELERATE = ID_USER_PACKET_ENUM + 13,
		ID_ACCELERATE_PLANE = ID_USER_PACKET_ENUM + 14,
		ID_ASK_TO_DECELERATE = ID_USER_PACKET_ENUM + 15,
		ID_DECELERATE_PLANE = ID_USER_PACKET_ENUM + 16,
		ID_MOVE_PLANE = ID_USER_PACKET_ENUM + 17
	};
		
	RakNet::NetworkIDManager* m_NetworkIDManager;
	RakNet::RakPeerInterface* m_Peer;

	RakNet::SocketDescriptor m_SocketDescriptor;
	RakNet::Packet* m_Packet;

	RakNet::BitStream m_BSOut;

	std::vector<RakNet::SystemAddress> playersWhoAreReady;

	std::vector<Faction*> m_FactionList;
	std::vector<Player*> m_PlayerList;

	bool m_Running;

	clock_t m_currentTime;
	clock_t m_elapsedTime;
	
	irr::IrrlichtDevice* m_Device;
	irr::scene::ISceneManager* m_SceneManager; 

	Server();

public:

	static Server* GetSingleton();
	~Server();

	unsigned char GetPacketIdentifier();
	
	void Reply();
	void Broadcast();
	void BroadcastToPlayersWhoAreReady();
	
	void SendMap();
	void SendFactions();
	void SendPlayers();
	void SendPlayerStates();

	void NewPlayer();
	void NewPlane();
	
	void PlayerEnterFaction();
	void AcceleratePlane();
	void DeceleratePlane();
	void MovePlanes();

	Player* getPlayerByName(RakNet::RakString nickname);

	int Run();
};