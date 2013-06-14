#include "server_manager.h"

using namespace std;

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

}

void server_manager::addServer(std::string name, std::string ip, std::string port)
{
	for (unsigned int i=0; i < servers.size(); i++)
		if (servers[i][0] == name)
			return;
	string tmp[3] = {name, ip, port};
	servers.push_back(tmp);
}

void server_manager::updateXML()
{

}