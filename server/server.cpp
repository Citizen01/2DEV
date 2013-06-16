#include "server.h"

#include "physic_engine.h"
#include "projectile.h"

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
	
	m_CurrentTime = clock();
	m_ElapsedTime = clock();
	
	m_Device = createDevice(video::EDT_NULL);
	m_SceneManager = m_Device->getSceneManager();

	m_Map = NULL;
}

Server* Server::getSingleton()
{
	if (!m_Instance)
	{
		m_Instance = new Server();
	}
	return m_Instance;
}


Server::~Server()
{
	m_Peer->Shutdown(300);
	RakPeerInterface::DestroyInstance(m_Peer);
}

unsigned char Server::getPacketIdentifier()
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

void Server::reply()
{
	m_Peer->Send(&m_BSOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_Packet->systemAddress, false);
}

void Server::broadcast()
{
	m_Peer->Send(&m_BSOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Server::broadcastToPlayersWhoAreReady()
{
	for(unsigned int i = 0; i < m_PlayersWhoAreReady.size() ; i++)
	{
		m_Peer->Send(&m_BSOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_PlayersWhoAreReady[i], false);
	}
}

void Server::sendMap()
{
	cout << "Sending the map to a client." << endl;

	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_ANSWER_TO_MAP);
	m_BSOut.Write("mountain");

	reply();
}

void Server::sendFactions()
{
	cout << "Sending the factions to a client." << endl;

	m_BSOut.Reset();

	m_BSOut.Write((MessageID)ID_ANSWER_TO_FACTIONS);
	m_BSOut.Write(m_FactionList.size());

	for(unsigned int i = 0; i < m_FactionList.size(); i++)
	{
		m_BSOut.Write(m_FactionList[i]->getRakName());
		m_BSOut.Write(m_FactionList[i]->GetNetworkID());
	}

	reply();
}

void Server::sendPlayers()
{
	cout << "Sending the players to a client." << endl;

	m_BSOut.Reset();

	m_BSOut.Write((MessageID)ID_ANSWER_TO_PLAYERS);
	m_BSOut.Write(m_PlayerList.size());

	for(unsigned int i = 0; i < m_PlayerList.size(); i ++)
	{
		m_BSOut.Write(m_PlayerList[i]->getRakNickName());
		m_BSOut.Write(m_PlayerList[i]->GetNetworkID());
	}

	reply();
}

void Server::newPlayer()
{
	cout << "Broadcasting a new player." << endl;

	m_PlayersWhoAreReady.push_back(m_Packet->systemAddress);

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

	broadcast();
}

void Server::newPlane()
{
	cout << "Broadcasting a new plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	if(player->getPlane() == NULL)
	{
		RakString planeName;
		bsIn.Read(planeName);
		player->setPlane(planeName);
						
		m_BSOut.Reset();
						
		m_BSOut.Write((MessageID)ID_PLAYER_GET_PLANE);
		m_BSOut.Write(playerNetworkID);
		m_BSOut.Write(planeName);

		broadcast();
	}

}

void Server::playerEnterFaction()
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

	if(faction->hasPlayer(player))
	{
		m_BSOut.Write((MessageID)ID_PLAYER_DO_NOT_ENTER_FACTION);
		m_BSOut.Write("You are already in this faction.");

		reply();
	}
	else if(faction != m_NetworkIDManager->GET_OBJECT_FROM_ID<Faction*>(1) && faction->getPlayers().size() == 10) //TODO: remplacer par max faction slots
	{
		m_BSOut.Write((MessageID)ID_PLAYER_DO_NOT_ENTER_FACTION);
		m_BSOut.Write("There is no more available slots in this faction.");

		reply();
	}
	else
	{
		if(player->getFaction() != NULL)
		{
			player->getFaction()->removePlayer(player);
		}
		faction->addPlayer(player);

		m_BSOut.Write((MessageID)ID_PLAYER_ENTER_FACTION);
		m_BSOut.Write(factionNetworkID);
		m_BSOut.Write(playerNetworkID);

		broadcast();
	}
}

void Server::sendPlayerStates()
{
	cout << "Sending players in factions and planes." << endl;

	for(unsigned int i = 0; i < m_PlayerList.size(); i ++)
	{
		if(m_PlayerList[i]->getFaction() != NULL)
		{
			m_BSOut.Reset();

			m_BSOut.Write((MessageID)ID_PLAYER_ENTER_FACTION);
			m_BSOut.Write(m_PlayerList[i]->getFaction()->GetNetworkID());
			m_BSOut.Write(m_PlayerList[i]->GetNetworkID());

			reply();
		}

		if(m_PlayerList[i]->getPlane() != NULL)
		{
			m_BSOut.Reset();

			m_BSOut.Write((MessageID)ID_PLAYER_GET_PLANE);
			m_BSOut.Write(m_PlayerList[i]->GetNetworkID());
			m_BSOut.Write(m_PlayerList[i]->getPlane()->getRakName());

			reply();
		}
	}
}

void Server::sendProjectiles()
{
	cout << "Sending players in factions and planes." << endl;

	for(unsigned int i = 0; i < m_ProjectileList.size(); i ++)
	{
		m_BSOut.Reset();

		m_BSOut.Write((MessageID)ID_SHOOT_MISSILE);
		m_BSOut.Write(m_ProjectileList[i]->getOwner()->GetNetworkID());
		m_BSOut.Write(m_ProjectileList[i]->GetNetworkID());
		m_BSOut.Write(m_ProjectileList[i]->getModelType());

		reply();
	}
}

void Server::acceleratePlane()
{
	cout << "Accelerating a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	player->getPlane()->incrementEnginePower();
						
	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_ACCELERATE_PLANE);
	m_BSOut.Write(playerNetworkID);

	broadcast();
}

void Server::deceleratePlane()
{
	cout << "Decelerating a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	player->getPlane()->decrementEnginePower();
						
	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_DECELERATE_PLANE);
	m_BSOut.Write(playerNetworkID);

	broadcast();
}

void Server::divePlane()
{
	cout << "Diving a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
	
	physics_engine::getSingleton()->rotate(player->getPlane()->getBody(), btVector3(0.1, 0, 0));
}

void Server::straightenPlane()
{
	cout << "Straigthening a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
	
	physics_engine::getSingleton()->rotate(player->getPlane()->getBody(), btVector3(-0.1, 0, 0));
}

void Server::rollLeftPlane()
{
	cout << "Rolling left a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
	
	physics_engine::getSingleton()->rotate(player->getPlane()->getBody(), btVector3(0, 0, 0.1));
}

void Server::rollRightPlane()
{
	cout << "Rolling right a plane." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);
	
	physics_engine::getSingleton()->rotate(player->getPlane()->getBody(), btVector3(0, 0, -0.1));
}

void Server::shootMissile()
{
	cout << "Shooting a missile." << endl;

	BitStream bsIn(m_Packet->data, m_Packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
						
	NetworkID playerNetworkID;
	bsIn.Read(playerNetworkID);
	Player* player = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(playerNetworkID);

	NetworkID targetNetworkID;
	bsIn.Read(targetNetworkID);
	Plane* target = NULL;
	if(targetNetworkID != UNASSIGNED_NETWORK_ID)
	{
		target = m_NetworkIDManager->GET_OBJECT_FROM_ID<Player*>(targetNetworkID)->getPlane();
	}
	Projectile* projectile = new Projectile(player, m_NetworkIDManager, RakString("missile"), unsigned int(5000), 1100, target);
	m_ProjectileList.push_back(projectile);

	m_BSOut.Reset();
						
	m_BSOut.Write((MessageID)ID_SHOOT_MISSILE);
	m_BSOut.Write(playerNetworkID);
	m_BSOut.Write(projectile->GetNetworkID());
	m_BSOut.Write(RakString("missile"));

	broadcast();
}

void Server::movePlanes()
{
	m_ElapsedTime = clock();
	clock_t deltaTime = m_ElapsedTime - m_CurrentTime;
	if(deltaTime > 40)
	{
		for(unsigned int i = 0; i < m_PlayerList.size(); i ++)
		{
			Plane* plane = m_PlayerList[i]->getPlane();
			if(plane != NULL)
			{
				cout << "Moving planes." << endl;

				//Bullet simulation
				physics_engine::getSingleton()->updatePhysics(deltaTime);

				btRigidBody* body = plane->getBody();
				btTransform transform = body->getWorldTransform();
				int power = plane->getEnginePower();
				int maxSpeed = plane->getMaxSpeed();
				int stallSpeed = plane->getStallSpeed();

				body->activate(true);
								
				btVector3 localVelocity = transform.getBasis().transpose() * body->getLinearVelocity();
				btVector3 absoluteVelocity = body->getLinearVelocity();

				float verticalVelocity = absoluteVelocity.getY();
				float horizontalVelocity = sqrt(pow(absoluteVelocity.getX(), 2) + pow(absoluteVelocity.getZ(), 2));
				float velocity = sqrt(pow(absoluteVelocity.getX(), 2) + pow(absoluteVelocity.getY(), 2) + pow(absoluteVelocity.getZ(), 2));

				body->applyCentralForce(transform.getBasis().getColumn(2) * maxSpeed * power);

				if(verticalVelocity < 0)
				{
					body->setGravity(btVector3(0, -10, 0));
				}
				else
				{
					if(horizontalVelocity > stallSpeed)
					{
						body->setGravity(btVector3(0, 20 * ((float)(horizontalVelocity - stallSpeed) / (maxSpeed - stallSpeed)), 0));
					}
					else if(horizontalVelocity < stallSpeed)
					{
						body->setGravity(btVector3(0, -(10 - (10 * (float)(horizontalVelocity) / stallSpeed)), 0));
					}
				}

				body->applyCentralForce(transform.getBasis().getColumn(0) * localVelocity.getX() * -maxSpeed);
				body->applyCentralForce(transform.getBasis().getColumn(1) * localVelocity.getY() * -maxSpeed);
				body->applyCentralForce(transform.getBasis().getColumn(2) * localVelocity.getZ() * -maxSpeed);

				core::vector3df position = plane->getPosition();
				core::vector3df rotation = plane->getRotation();

				//TODO: à supprimer
				cout << "(" << position.X << "," << position.Y << "," << position.Z << "),"
				<< "(" << rotation.X << "," << rotation.Y << "," << rotation.Z << ") "
				<< localVelocity.getX() << " | "
				<< localVelocity.getY() << " | "
				<< localVelocity.getZ() << " ||| "
				<< velocity <<endl;

				m_BSOut.Reset();

				m_BSOut.Write((MessageID)ID_MOVE_PLANE);

				m_BSOut.Write(m_PlayerList[i]->GetNetworkID());

				m_BSOut.Write(position.X);
				m_BSOut.Write(position.Y);
				m_BSOut.Write(position.Z);

				m_BSOut.Write(rotation.X);
				m_BSOut.Write(rotation.Y);
				m_BSOut.Write(rotation.Z);

				broadcastToPlayersWhoAreReady();
			}
		}
		m_CurrentTime = clock();
		updateProjectiles(deltaTime);
	}
}

void Server::updateProjectiles(unsigned int deltaTime)
{
	for(unsigned int i = 0; i < m_ProjectileList.size(); i ++)
	{
		cout << "Moving projectiles." << endl;

		Projectile* projectile = m_ProjectileList[i];
		btRigidBody* body = projectile->getBody();

		//Bullet simulation
		projectile->updateTimeToLive(deltaTime);

		body->activate(true);

		body->applyCentralForce(body->getWorldTransform().getBasis().getColumn(2) * projectile->getSpeed());

		m_BSOut.Reset();

		m_BSOut.Write((MessageID)ID_UPDATE_PROJECTILE);

		core::vector3df position = projectile->getPosition();
		core::vector3df rotation = projectile->getRotation();

		cout << projectile->getTimeToLive() << endl;

		m_BSOut.Write(projectile->GetNetworkID());

		m_BSOut.Write(position.X);
		m_BSOut.Write(position.Y);
		m_BSOut.Write(position.Z);

		m_BSOut.Write(rotation.X);
		m_BSOut.Write(rotation.Y);
		m_BSOut.Write(rotation.Z);

		broadcastToPlayersWhoAreReady();
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

int Server::run()
{
	if(m_Map == NULL)
	{
		m_Map = new Map("mountain");
	}
	while (m_Running)
	{
		
		for (m_Packet = m_Peer->Receive(); m_Packet; m_Peer->DeallocatePacket(m_Packet), m_Packet = m_Peer->Receive())
		{
			switch (getPacketIdentifier())
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
					sendMap();
					break;
				case ID_ASK_FOR_FACTIONS:
					sendFactions();
					break;
				case ID_ASK_FOR_PLAYERS:
					sendPlayers();
					break;
				case ID_ASK_FOR_PLAYERS_STATES:
					sendPlayerStates();
					break;
				case ID_ASK_FOR_PROJECTILES:
					sendProjectiles();
					break;

				case ID_ASK_FOR_LOCAL_PLAYER:
					newPlayer();
					break;
				case ID_ASK_FOR_LOCAL_PLANE:
					newPlane();
					break;

				case ID_ASK_TO_ENTER_FACTION:
					playerEnterFaction();
					break;

				case ID_ASK_TO_ACCELERATE:
					acceleratePlane();
					break;
				case ID_ASK_TO_DECELERATE:
					deceleratePlane();
					break;
				case ID_ASK_TO_DIVE:
					divePlane();
					break;
				case ID_ASK_TO_STRAIGHTEN:
					straightenPlane();
					break;
				case ID_ASK_TO_ROLL_LEFT:
					rollLeftPlane();
					break;
				case ID_ASK_TO_ROLL_RIGHT:
					rollRightPlane();
					break;

				case ID_ASK_TO_SHOOT_MISSILE:
					shootMissile();
					break;
			
				default:
					cout << "Message with identifier " << (int)m_Packet->data[0] << " has arrived." << endl;
					break;
			}
		}
		movePlanes();
	}

	return 0;
}