#pragma once

#include <string>
#include <vector>

struct server
{
	std::string name;
	std::string ip;
	std::string port;
};

class server_manager
{
private:
	static server_manager* instance;
	server_manager(void);

	//Serverlist
	std::vector<server> servers;
	

public:
	static server_manager* getSingleton();
	~server_manager(void);

	//Permet de charger la liste des servers depuis le fichier XML
	void loadServers();

	//Permet de rajouter un server dans la liste et dans le XML
	void addServer(std::string name, std::string ip, std::string port);

	//Met à jour le contenu du xml en fonction de la liste actuelle
	void updateXML();

	//Permet de récupérer une référence vers la liste des servers
	std::vector<server>& getServerList();
};

