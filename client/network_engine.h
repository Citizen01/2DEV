#pragma once

#include "engine.h"

#include <vector>

#include "NetworkIDManager.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID

#include "faction.h"
#include "player.h"

class engine;

class network_engine : public engine
{
	public:

		network_engine(App* a);
		~network_engine(void);

		void connect(char* ip, int port);
		void disconnect();
		
		RakNet::NetworkIDManager* GetNetworkIDManager();

		unsigned char GetPacketIdentifier(RakNet::Packet* packet);

		void GetReady();

		void askForMap();
		void askForFactions();
		void askForPlayers();
		void askForPlayersStates();

		void askForLocalPlayer();
		void askForLocalPlane(std::string planeModel);

		void askToEnterFaction(Faction* faction);
		void askToAccelerate();
		void askToDecelerate();
		
		void getMap();
		void getFactions();
		void getPlayers();

		void playerEnterFaction();
		void playerGetPlane();

		void acceleratePlane();
		void deceleratePlane();
		void movePlane();

		void readMessage();

		void frame();
		void on_engines_linked();

		// Fonction qui récupère tous les events
		bool OnEvent(const irr::SEvent& event);

	private:

		char* m_ServerIP;
		int m_ServerPort;

		bool m_Connected;
		
		RakNet::NetworkIDManager* m_NetworkIDManager;
		RakNet::RakPeerInterface* m_Peer;

		RakNet::SocketDescriptor m_SocketDescriptor;
		RakNet::SystemAddress m_ServerAddress;
	
		RakNet::Packet* m_Packet;

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
};
