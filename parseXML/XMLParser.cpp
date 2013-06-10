#include "XMLParser.h"

XMLParser::XMLParser()
{
	xml_document<> m_Doc;
}

bool XMLParser::OpenXML(string fileName)
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

void XMLParser::CoreConfig(/*Local_Player Player */)
{
	OpenXML("../config/coreconfig.xml");

	xml_node<> *root_node = m_Doc.first_node();
	cout << root_node->name() << endl;
	
	for(xml_node<> *settings_nodes = root_node->first_node("settings")->first_node(); settings_nodes; settings_nodes = settings_nodes->next_sibling())
	{
		
		cout << "Setting : "  << settings_nodes->name() << " : " << settings_nodes->value() << endl;
	}

	for(xml_node<> *binds_nodes = root_node->first_node("binds")->first_node(); binds_nodes; binds_nodes = binds_nodes->next_sibling())
	{
		cout << "Bind : " << binds_nodes->first_attribute()->value() << " : " << binds_nodes->value() << endl;
	}
}