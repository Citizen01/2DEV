#include "XMLParser.h"
#include "app.h"
#include "server_manager.h"
#include "utils.h"

using namespace rapidxml;
using namespace std;
using namespace irr;
using namespace constants;

XMLParser::XMLParser(string fileName)
{
	xml_document<> m_Doc;
	openXML(fileName);
}

bool XMLParser::openXML(string fileName)
{
	ifstream file(fileName);
	if(file.fail())
	{
		return false;
	}

	buffer = vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	m_Doc.clear();
	m_Doc.parse<0>(&buffer[0]);

	return true;
}

bool XMLParser::populateSettings(map<string, string> &settings)
{
	xml_node<> *root_node = m_Doc.first_node();
	if (root_node != 0)
	{
		for(xml_node<> *settings_nodes = root_node->first_node("settings")->first_node(); settings_nodes; settings_nodes = settings_nodes->next_sibling())
		{
			string settings_name = settings_nodes->name();
			string settings_value = settings_nodes->value();
			settings[settings_name] = settings_value;
			cout << "Settings name : "<< settings_name << "settings value : "<< settings_value << endl;
		}
		return true;
	}
	else return false;
}

bool XMLParser::populateBind(map<ACTION_CODE, EKEY_CODE> &binds)
{
	xml_node<> *root_node = m_Doc.first_node();
	if (root_node != 0)
	{
		for(xml_node<> *binds_nodes = root_node->first_node("binds")->first_node(); binds_nodes; binds_nodes = binds_nodes->next_sibling())
		{
			ACTION_CODE action_code = strToActionCode(binds_nodes->first_attribute()->value());
			EKEY_CODE ekey_code = strToEkeyCode(binds_nodes->value());
			binds[action_code] = ekey_code;
		}
		return true;
	}
	else return false;
}

map<char*, vector<attribut>> XMLParser::getMapping(string filePath)
{
	xml_node<> *root_node = m_Doc.first_node();
	map<char*, vector<attribut>> mapping;

	if (root_node != 0)
	{
		for(xml_node<> *map_node = root_node->first_node(); map_node; map_node = map_node->next_sibling())
		{
			vector<attribut> tmpvect;

			for(xml_attribute<char> *attribute = map_node->first_attribute(); attribute; attribute = attribute->next_attribute())
			{ 
				attribut tmpattr;
				tmpattr.name = attribute->name();
				tmpattr.value = attribute->value();

				tmpvect.push_back(tmpattr);
			}
			mapping[map_node->name()] = tmpvect;
		}
	}
	return mapping;
}

void XMLParser::loadServerList()
{
	xml_node<> *root_node = m_Doc.first_node();
	if (root_node != 0)
	{
		server_manager* srvmgr = server_manager::getSingleton();
		for(xml_node<> *server_node = root_node->first_node(); server_node; server_node = server_node->next_sibling())
		{
			string name = server_node->first_attribute("name")->value();
			string ip = server_node->first_attribute("ip")->value();
			string port = server_node->first_attribute("port")->value();
			
			srvmgr->addServer(name, ip, port);
		}
	}
}

void XMLParser::saveServerList()
{
	xml_node<> *root_node = m_Doc.first_node();
	if (root_node != 0)
		return;

	//Vide le node
	root_node->remove_all_nodes();

	//Remplit le node
	std::vector<server> serverlist = server_manager::getSingleton()->getServerList();
	for(unsigned int i=0; i < serverlist.size(); i++)
	{
		//server node
		xml_node<> *node = m_Doc.allocate_node(node_element, "server", "");
		m_Doc.append_node(node);

		server srv = serverlist[i];

		//attribut name:
		xml_attribute<> *name = m_Doc.allocate_attribute("name", srv.name.c_str());
		node->append_attribute(name);

		//attribut ip:
		xml_attribute<> *ip = m_Doc.allocate_attribute("ip", srv.ip.c_str());
		node->append_attribute(ip);

		//attribut port:
		xml_attribute<> *port = m_Doc.allocate_attribute("port", srv.port.c_str());
		node->append_attribute(port);

		// Save to file
		/*std::ofstream file_stored("../config/file_stored.xml");
		file_stored << m_Doc;
		file_stored.close();*/
	}
}

XMLParser::~XMLParser() 
{
	//xml_base::name_size();
	//xml_base::value_size();

	m_Doc.clear();
	buffer.clear();
}