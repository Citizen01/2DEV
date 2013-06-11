#include "server.h"

using namespace std;
using namespace RakNet;
using namespace irr;

Server* Server::m_Instance = NULL;

Server::Server()
{
	m_NetworkIDManager = NetworkIDManager::GetInstance();
	m_Peer = RakPeerInterface::GetInstance();

	SocketDescriptor m_SocketDescriptor(SERVER_PORT,0);
	
	m_Peer->Startup(MAX_CLIENTS, &m_SocketDescriptor, 1);
	m_Peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	cout << "Starting the server." << endl;

	m_FactionList.push_back(new Faction("Spectateurs", m_NetworkIDManager, 1));
	m_FactionList.push_back(new Faction("Equipe 1", m_NetworkIDManager, 2));
	m_FactionList.push_back(new Faction("Equipe 2", m_NetworkIDManager, 3));

	vector<SystemAddress> playersWhoAreReady;

	m_Running = true;
	
	m_currentTime = clock();
	m_elapsedTime = clock();
	
	m_Device = createDevice(video::EDT_NULL);
	m_SceneManager = m_Device->getSceneManager();
}

Server* Server::GetSingleton()
{
	if (!m_Instance)
		m_Instance = new Server();
	return m_Instance;
}


Server::~Server()
{
	m_Peer->Shutdown(300);
	RakPeerInterface::DestroyInstance(m_Peer);
}

unsigned char Server::GetPacketIdentifier()
{
	if ((unsigned char) m_Packet->data[0] == ID_TIMESTAMP)
	{
		return (unsigned char) m_Packet->data[sizeof(unsigned char) + sizeof(Time)];
	}
	else
	{
		return (unsigned char) m_Packet->data[0];
	}
}

void Server::Reply()
{
	m_Peer->Send(&m_BSOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_Packet->systemAddress, false);
}

void Server::Broadcast()
{
	m_Peer->Send(&m_BSOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Server::BroadcastToPlayersWhoAreReady()
{
	for(unsigned int i = 0; i < playersWhoAreReady.size() ; i++)
	{
		m_Peer->Send(&m_BSOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playersWhoAreReady[i], false);
	}
}

void Server::SendMap()
{
	cout << "Sending the map to a client." << endl;

	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_ANSWER_TO_MAP);
	m_BSOut.Write("mountain");

	Reply();
}

void Server::SendFactions()
{
	cout << "Sending the factions to a client." << endl;

	m_BSOut.Reset();

	m_BSOut.Write((MessageID)ID_ANSWER_TO_FACTIONS);
	m_BSOut.Write(m_FactionList.size());

	for(unsigned int i = 0; i < m_FactionList.size(); i ++)
	{
		m_BSOut.Write(m_FactionList[i]->GetRakName());
		m_BSOut.Write(m_FactionList[i]->GetNetworkID());
	}

	Reply();
}

void Server::SendPlayers()
{
	cout << "Sending the players to a client." << endl;

	m_BSOut.Reset();

	m_BSOut.Write((MessageID)ID_ANSWER_TO_PLAYERS);
	m_BSOut.Write(m_PlayerList.size());

	for(unsigned int i = 0; i < m_PlayerList.size(); i ++)
	{
		m_BSOut.Write(m_PlayerList[i]->GetRakName());
		m_BSOut.Write(m_PlayerList[i]->GetNetworkID());
	}

	Reply();
}

void Server::NewPlayer()
{
	cout << "Broadcasting a new player." << endl;

	playersWhoAreReady.push_back(m_Packet->systemAddress);

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	RakString playerName;
	bsIn.Read(playerName);
	m_PlayerList.push_back(new Player(playerName, m_NetworkIDManager));

	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_ANSWER_TO_PLAYERS);
	m_BSOut.Write(1);
	m_BSOut.Write(playerName);
	m_BSOut.Write(getPlayerByName(playerName)->GetNetworkID());

	Broadcast();
}

void Server::NewPlane()
{
	cout << "Broadcasting a new plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	if(player->GetPlane() == NULL)
	{
		RakString planeName;
		bsIn.Read(planeName);
		player->SetPlane(planeName, m_SceneManager);
						
		m_BSOut.Reset();
						
		m_BSOut.Write((MessageID)ID_PLAYER_GET_PLANE);
		m_BSOut.Write(playerNetworkID);
		m_BSOut.Write(planeName);

		Broadcast();
	}

}

void Server::PlayerEnterFaction()
{
	cout << "Managing player in factions." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID factionNetworkID;
	bsIn.Read(factionNetworkID);
	Faction* faction = m_NetworkIDManager->GET_OBJECT_FROM_ID<Faction*>(factionNetworkID);

	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
						
	m_BSOut.Reset();

	if(faction->HasPlayer(player))
	{
		m_BSOut.Write((MessageID)ID_PLAYER_DO_NOT_ENTER_FACTION);
		m_BSOut.Write("You are already in this faction.");

		Reply();
	}
	else if(faction != m_NetworkIDManager->GET_OBJECT_FROM_ID<Faction*>(1) && faction->GetPlayers().size() == 10) //TODO remplacer par max faction slots
	{
		m_BSOut.Write((MessageID)ID_PLAYER_DO_NOT_ENTER_FACTION);
		m_BSOut.Write("There is no more available slots in this faction.");

		Reply();
	}
	else
	{
		if(player->GetFaction() != NULL)
		{
			player->GetFaction()->RemovePlayer(player);
		}
		faction->AddPlayer(player);

		m_BSOut.Write((MessageID)ID_PLAYER_ENTER_FACTION);
		m_BSOut.Write(factionNetworkID);
		m_BSOut.Write(playerNetworkID);

		Broadcast();
	}
}

void Server::SendPlayerStates()
{
	cout << "Sending players in factions, and planes." << endl;

	for(unsigned int i = 0; i < m_PlayerList.size(); i ++)
	{
		if(m_PlayerList[i]->GetFaction() != NULL)
		{
			m_BSOut.Reset();

			m_BSOut.Write((MessageID)ID_PLAYER_ENTER_FACTION);
			m_BSOut.Write(m_PlayerList[i]->GetFaction()->GetNetworkID());
			m_BSOut.Write(m_PlayerList[i]->GetNetworkID());

			Reply();
		}
		if(m_PlayerList[i]->GetPlane() != NULL)
		{
			m_BSOut.Reset();

			m_BSOut.Write((MessageID)ID_PLAYER_GET_PLANE);
			m_BSOut.Write(m_PlayerList[i]->GetNetworkID());
			m_BSOut.Write(m_PlayerList[i]->GetPlane()->GetRakName());

			Reply();
		}
	}
}

void Server::AcceleratePlane()
{
	cout << "Accelerating a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	player->GetPlane()->IncrementEnginePower();
						
	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_ACCELERATE_PLANE);
	m_BSOut.Write(playerNetworkID);

	Broadcast();
}

void Server::DeceleratePlane()
{
	cout << "Decelerating a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	player->GetPlane()->DecrementEnginePower();
						
	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_DECELERATE_PLANE);
	m_BSOut.Write(playerNetworkID);

	Broadcast();
}

void Server::MovePlanes()
{
	
	m_elapsedTime = clock();
	if(m_elapsedTime - m_currentTime > 40)
	{

		for(unsigned int i = 0; i < m_PlayerList.size(); i ++)
		{
			if(m_PlayerList[i]->GetPlane() != NULL)
			{
				//cout << "Moving planes." << endl;
				float distance = m_PlayerList[i]->GetPlane()->GetEnginePower();
				core::vector3df position = moveNodeInLocalSpace(m_PlayerList[i]->GetPlane()->getMesh(), core::vector3df(0, 0, 1), distance);
				core::vector3df rotation = rotateNodeInLocalSpace(m_PlayerList[i]->GetPlane()->getMesh(), core::vector3df(0, 1, 0), 0.f);

				m_BSOut.Reset();

				m_BSOut.Write((MessageID)ID_MOVE_PLANE);

				m_BSOut.Write(m_PlayerList[i]->GetNetworkID());

				m_BSOut.Write(position.X);
				m_BSOut.Write(position.Y);
				m_BSOut.Write(position.Z);

				m_BSOut.Write(rotation.X);
				m_BSOut.Write(rotation.Y);
				m_BSOut.Write(rotation.Z);

				BroadcastToPlayersWhoAreReady();
			}
		}
		m_currentTime = clock();
	}
}

Player* Server::getPlayerByName(RakString nickname)
{
	for each (Player* player in m_PlayerList)
	{
		if (player->getNickname() == nickname.C_String())
			return player;
	}
	return NULL;
}

int Server::Run()
{
	while (m_Running)
	{
		for (m_Packet = m_Peer->Receive(); m_Packet; m_Peer->DeallocatePacket(m_Packet), m_Packet = m_Peer->Receive())
		{
			switch (GetPacketIdentifier())
			{
				case ID_NEW_INCOMING_CONNECTION:
					cout << "A connection is incoming." << endl;
					break;

				case ID_DISCONNECTION_NOTIFICATION:
					cout << "A client has disconnected." << endl;
					break;
				case ID_CONNECTION_LOST:
					cout << "A client lost the connection." << endl;
					break;
				
				case ID_ASK_FOR_MAP:
					SendMap();
					break;
				case ID_ASK_FOR_FACTIONS:
					SendFactions();
					break;
				case ID_ASK_FOR_PLAYERS:
					SendPlayers();
					break;
				case ID_ASK_FOR_PLAYERS_STATES:
					SendPlayerStates();
					break;

				case ID_ASK_FOR_LOCAL_PLAYER:
					NewPlayer();
					break;
				case ID_ASK_FOR_LOCAL_PLANE:
					NewPlane();
					break;

				case ID_ASK_TO_ENTER_FACTION:
					PlayerEnterFaction();
					break;
				case ID_ASK_TO_ACCELERATE:
					AcceleratePlane();
					break;
				case ID_ASK_TO_DECELERATE:
					DeceleratePlane();
					break;
			
				default:
					cout << "Message with identifier " << (int)m_Packet->data[0] << " has arrived." << endl;
					break;
			}
		}
		MovePlanes();
	}

	return 0;
}