#pragma once

#include <string>
#include <vector>

class server_manager
{
private:
	static server_manager* instance;
	server_manager(void);

	//Serverlist
	std::vector<std::string[3]> servers;
	

public:
	static server_manager* getSingleton();
	~server_manager(void);

	//Permet de charger la liste des servers depuis le fichier XML
	void loadServers();

	//Permet de rajouter un server dans la liste et dans le XML
	void addServer(std::string name, std::string ip, std::string port);

	//Met � jour le contenu du xml en fonction de la liste actuelle
	void updateXML();
};

