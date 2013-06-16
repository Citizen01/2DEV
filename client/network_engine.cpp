#include "network_engine.h"
#include <iostream>
#include "app.h"
#include "projectile.h"
#include "unistd.h" //Pour la fonction sleep
#include "ui_windows.h"

using namespace std;
using namespace RakNet;


network_engine::network_engine(App* a) : engine(a)
{
	cout << "Starting the network engine." << endl;

	m_Connected = false;

	m_NetworkIDManager = NetworkIDManager::GetInstance();
	m_Peer = RakPeerInterface::GetInstance();
}

network_engine::~network_engine(void)
{
	disconnect();
	cout << "Stopping the network engine." << endl;
	RakPeerInterface::DestroyInstance(m_Peer);
}

void network_engine::connect(char* ip, int port)
{
	m_ServerIP = ip;
	m_ServerPort = port;

	cout << "Connecting to the server " << m_ServerIP << ":" << m_ServerPort << endl;
	m_Peer->Startup(1, &m_SocketDescriptor, 1);
	m_Peer->Connect(m_ServerIP, m_ServerPort, 0,0);

	//Essaye de se connecter 1 fois par seconde et 10 fois
	int maxAttempts = 10;
	int attempts = 1;
	int code = -1;
	do{
		cout << "Connection attempt #" << attempts << endl;
		Sleep(1000);
		for (m_Packet = m_Peer->Receive(); m_Packet; m_Peer->DeallocatePacket(m_Packet), m_Packet = m_Peer->Receive())
		{
			m_ServerAddress = m_Packet->systemAddress;
			code = GetPacketIdentifier(m_Packet);
		}
	} while( code == -1 && attempts++ < maxAttempts);
	
	switch (code)
	{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				cout << "Our connection request has been accepted." << endl;
				m_Connected = true;
				show_main_menu(false);
				askForMap();
			}
			break;
		case ID_ALREADY_CONNECTED:
			cout << "We are already connected." << endl;
			break;	
		case ID_CONNECTION_ATTEMPT_FAILED:
			cout << "Connection timed out !" << endl;
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			cout << "The server is full." << endl;
			break;
		default:
			cout << "Message with identifier " << (int)m_Packet->data[0] << " has arrived." << endl;
			break;
	}
}

void network_engine::disconnect()
{
	if (!m_Connected)
		return;

	cout << "Disconnecting from the server." << endl;
	m_Peer->Shutdown(300);
	m_Connected = false;
}

NetworkIDManager* network_engine::GetNetworkIDManager()
{
	return m_NetworkIDManager;
}

unsigned char network_engine::GetPacketIdentifier(Packet* packet)
{
	if ((unsigned char) packet->data[0] == ID_TIMESTAMP)
	{
		return (unsigned char) packet->data[sizeof(unsigned char) + sizeof(Time)];
	}
	else
	{
		return (unsigned char) packet->data[0];
	}
}

void network_engine::GetReady()
{
	if (!m_Connected)
		return;

	if(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer() == NULL)
	{
		askForLocalPlayer();
	}
	else if(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetFaction() == NULL)
	{
		askToEnterFaction(m_NetworkIDManager->GET_OBJECT_FROM_ID<Faction*>(1));
	}
	else
	{
		askForLocalPlane("SU 25");
	}
}

void network_engine::askForMap()
{
	if (!m_Connected)
		return;

	cout << "Asking the server for the map." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_FOR_MAP);
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askForFactions()
{
	if (!m_Connected)
		return;

	cout << "Asking the server for factions." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_FOR_FACTIONS);
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askForPlayers()
{
	if (!m_Connected)
		return;

	cout << "Asking the server for players." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_FOR_PLAYERS);
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askForLocalPlayer()
{
	if (!m_Connected)
		return;

	cout << "Asking the server for our own player : " + App::getSingleton()->settings["nickname"] << endl;

	RakString playerName(App::getSingleton()->settings["nickname"].c_str());

	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_FOR_LOCAL_PLAYER);
	bsOut.Write(playerName);
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askForLocalPlane(string planeModel)
{
	if (!m_Connected)
		return;

	cout << "Asking the server for our own plane." << endl;

	RakString planeName(planeModel.c_str());

	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_FOR_LOCAL_PLANE);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	bsOut.Write(planeName);
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askForPlayersStates()
{
	if (!m_Connected)
		return;

	cout << "Asking the server for players in factions, and planes." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_FOR_PLAYERS_STATES);
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askForProjectiles()
{
	cout << "Asking the server for projectiles." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_FOR_PROJECTILES);
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToEnterFaction(Faction* faction)
{
	if (!m_Connected)
		return;

	cout << "Asking the server to enter a faction." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_ENTER_FACTION);
	bsOut.Write(faction->GetNetworkID());
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToAccelerate()
{
	if (!m_Connected)
		return;

	cout << "Asking the server to accelerate." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_ACCELERATE);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToDecelerate()
{
	if (!m_Connected)
		return;

	cout << "Asking the server to decelerate." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_DECELERATE);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToDive()
{
	cout << "Asking the server to dive." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_DIVE);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToStraighten()
{
	cout << "Asking the server to straighten." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_STRAIGHTEN);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToRollLeft()
{
	cout << "Asking the server to roll left." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_ROLL_LEFT);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToRollRight()
{
	cout << "Asking the server to roll right." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_ROLL_RIGHT);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::askToShootMissile(Plane* target)
{
	cout << "Asking the server to shoot a missile." << endl;
	BitStream bsOut;
	bsOut.Write((MessageID)ID_ASK_TO_SHOOT_MISSILE);
	bsOut.Write(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer()->GetNetworkID());
	if(target != NULL)
	{
		bsOut.Write(target->getPilot()->GetNetworkID());
	}
	else
	{
		bsOut.Write(UNASSIGNED_NETWORK_ID);
	}
	m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_ServerAddress, false);
}

void network_engine::getMap()
{
	if (!m_Connected)
		return;

	cout << "Receiving the server's map." << endl;

	RakString mapName = "";

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	bsIn.Read(mapName);
	App::getSingleton()->getGameEngine()->LaunchGame(mapName.C_String());

	askForFactions();
}

void network_engine::getFactions()
{
	if (!m_Connected)
		return;

	cout << "Receiving the server's factions." << endl;

	unsigned int factionCount = 0;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	bsIn.Read(factionCount);
	for(unsigned int i = 0; i < factionCount; i ++)
	{
		RakString factionName = "";
		NetworkID factionNetworkID;
		
		bsIn.Read(factionName);
		bsIn.Read(factionNetworkID);

		App::getSingleton()->getGameEngine()->GetGame()->addFaction(factionName.C_String(), m_NetworkIDManager, factionNetworkID);
	}

	askForPlayers();
}

void network_engine::getPlayers()
{
	if (!m_Connected)
		return;

	cout << "Receiving the server's players." << endl;

	unsigned int playerCount = 0;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	bsIn.Read(playerCount);
	for(unsigned int i = 0; i < playerCount; i ++)
	{
		RakString playerName = "";
		NetworkID playerNetworkId;

		bsIn.Read(playerName);
		bsIn.Read(playerNetworkId);

		App::getSingleton()->getGameEngine()->GetGame()->addPlayer(playerName, m_NetworkIDManager, playerNetworkId);
	}

	if(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer() == NULL)
	{
		askForPlayersStates();
	}
}

void network_engine::playerEnterFaction()
{
	if (!m_Connected)
		return;

	cout << "A player entered a faction." << endl;
	
	NetworkID factionNetworkID;
	NetworkID playerNetworkID;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	bsIn.Read(factionNetworkID);
	bsIn.Read(playerNetworkID);

	Faction* faction = m_NetworkIDManager->GET_OBJECT_FROM_ID<Faction*>(factionNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	if(player->GetFaction() != NULL)
	{
		player->GetFaction()->RemovePlayer(player);
	}
	faction->AddPlayer(player);
}

void network_engine::playerGetPlane()
{
	if (!m_Connected)
		return;

	cout << "A player got her/his plane." << endl;
	
	NetworkID playerNetworkID;
	RakString planeModel;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	bsIn.Read(planeModel);

	player->SetPlane(planeModel.C_String());

	if(App::getSingleton()->getGameEngine()->GetGame()->getLocalPlayer() == NULL)
	{
		askForProjectiles();
	}
}

void network_engine::acceleratePlane()
{
	if (!m_Connected)
		return;

	cout << "Accelerating a plane." << endl;
	
	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
					
	NetworkID playerNetworkID;	
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
	player->GetPlane()->IncrementEnginePower();
}

void network_engine::deceleratePlane()
{
	if (!m_Connected)
		return;

	cout << "Decelerating a plane." << endl;
	
	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
					
	NetworkID playerNetworkID;	
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
	player->GetPlane()->DecrementEnginePower();
}

void network_engine::shootMissile()
{
	cout << "Shooting a missile." << endl;
	
	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
					
	NetworkID playerNetworkID;	
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	NetworkID projectileNetworkID;
	bsIn.Read(projectileNetworkID);

	RakString model;
	bsIn.Read(model);

	App::getSingleton()->getGameEngine()->GetGame()->addProjectile(player, m_NetworkIDManager, projectileNetworkID, model);
}

void network_engine::movePlane()
{
	if (!m_Connected)
		return;
	
	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
					
	NetworkID playerNetworkID;	
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
	
	float positionX;
	bsIn.Read(positionX);
	float positionY;
	bsIn.Read(positionY);
	float positionZ;
	bsIn.Read(positionZ);
	player->GetPlane()->SetPosition(core::vector3df(positionX, positionY, positionZ));

	float rotationX;
	bsIn.Read(rotationX);
	float rotationY;
	bsIn.Read(rotationY);
	float rotationZ;
	bsIn.Read(rotationZ);
	player->GetPlane()->SetRotation(core::vector3df(rotationX, rotationY, rotationZ));
}

void network_engine::updateProjectile()
{
	cout << "Moving a projectile." << endl;
	
	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
					
	NetworkID projectileNetworkID;	
	bsIn.Read(projectileNetworkID);
	Projectile* projectile = m_NetworkIDManager->GET_OBJECT_FROM_ID<Projectile*>(projectileNetworkID);
	
	float positionX;
	bsIn.Read(positionX);
	float positionY;
	bsIn.Read(positionY);
	float positionZ;
	bsIn.Read(positionZ);
	projectile->setPosition(core::vector3df(positionX, positionY, positionZ));

	float rotationX;
	bsIn.Read(rotationX);
	float rotationY;
	bsIn.Read(rotationY);
	float rotationZ;
	bsIn.Read(rotationZ);
	projectile->setRotation(core::vector3df(rotationX, rotationY, rotationZ));
}

void network_engine::readMessage()
{
	if (!m_Connected)
		return;

	RakString message;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	bsIn.Read(message);
	cout << message.C_String() << endl;
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void network_engine::frame()
{
	if(!m_Connected)
		return;

	for (m_Packet = m_Peer->Receive(); m_Packet; m_Peer->DeallocatePacket(m_Packet), m_Packet = m_Peer->Receive())
	{
		switch (GetPacketIdentifier(m_Packet))
		{
			case ID_DISCONNECTION_NOTIFICATION:
				cout << "We have been disconnected." << endl;
				m_Connected = false;
				break;
			case ID_CONNECTION_LOST:
				cout << "Connection lost." << endl;
				m_Connected = false;
				break;

			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				cout << "Another client has connected." << endl;
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				cout << "Another client has disconnected." << endl;
				break;
			case ID_REMOTE_CONNECTION_LOST:
				cout << "Another client has lost the connection." << endl;
				break;
			case ID_ANSWER_TO_MAP:
				getMap();
				break;
			case ID_ANSWER_TO_FACTIONS:
				getFactions();
				break;
			case ID_ANSWER_TO_PLAYERS:
				getPlayers();
				break;

			case ID_PLAYER_ENTER_FACTION:
				playerEnterFaction();
				break;
			case ID_PLAYER_DO_NOT_ENTER_FACTION:
				readMessage();
				break;
			case ID_PLAYER_GET_PLANE:
				playerGetPlane();
				break;
					
			case ID_ACCELERATE_PLANE:
				acceleratePlane();
				break;
			case ID_DECELERATE_PLANE:
				deceleratePlane();
				break;

			case ID_SHOOT_MISSILE:
				shootMissile();
				break;
					
			case ID_MOVE_PLANE:
				movePlane();
				break;
			case ID_UPDATE_PROJECTILE:
				updateProjectile();
				break;

			default:
				cout << "Unknown message with identifier " << (int)m_Packet->data[0] << " has arrived." << endl;
		}
	}
}

bool network_engine::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	return false;
}