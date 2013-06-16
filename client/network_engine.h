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
		void askForProjectiles();

		void askForLocalPlayer();
		void askForLocalPlane(std::string planeModel);

		void askToEnterFaction(Faction* faction);
		
		void askToAccelerate();
		void askToDecelerate();
		void askToDive();
		void askToStraighten();
		void askToRollLeft();
		void askToRollRight();
		void askToShootMissile(Plane* target = NULL);
		
		void getMap();
		void getFactions();
		void getPlayers();

		void playerEnterFaction();
		void playerGetPlane();
		
		void acceleratePlane();
		void deceleratePlane();
		void shootMissile();

		void movePlane();
		void updateProjectile();

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
};
