#include "server_manager.h"
#include "XMLParser.h"

using namespace std;

server_manager* server_manager::instance = NULL;

server_manager::server_manager(void)
{
}


server_manager::~server_manager(void)
{
}

server_manager* server_manager::getSingleton()
{
	if (!instance)
		instance = new server_manager();
	return instance;
}

void server_manager::loadServers()
{
	XMLParser serverParser("../config/serverlist.xml");
	serverParser.loadServerList();
}

bool server_manager::addServer(string name, string ip, string port)
{
	for (unsigned int i=0; i < servers.size(); i++)
		if (servers.at(i).name == name)
			return false;

	server srv;
	srv.name = name;
	srv.ip = ip;
	srv.port = port;
	servers.push_back(srv);
	updateXML();
	return true;
}

void server_manager::updateXML()
{
	XMLParser serverParser("../config/serverlist.xml");
	serverParser.saveServerList();
}

std::vector<server>& server_manager::getServerList()
{
	return servers;
}

bool server_manager::removeServer(string name)
{
	int pos = -1;
	for (unsigned int i = 0; i < servers.size(); i++)
	{
		if (servers[i].name == name)
		{
			pos = i;
			break;
		}
	}

	if (pos !=1)
	{
		servers.erase(servers.begin()+pos);
		updateXML();
		return true;
	}
	return false;
}