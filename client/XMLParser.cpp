#include "XMLParser.h"
#include "app.h"
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

XMLParser::~XMLParser() 
{
	//xml_base::name_size();
	//xml_base::value_size();

}