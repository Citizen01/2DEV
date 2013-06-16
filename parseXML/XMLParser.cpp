#include "XMLParser.h"
#include <map>

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

struct attribut{
	char* name;
	char* value;
};

void XMLParser::CoreConfig(/*Local_Player Player */)
{
	OpenXML("../config/coreconfig.xml");

	xml_node<> *root_node = m_Doc.first_node();
	cout << root_node->name() << endl;
	
	map<char*, vector<attribut>> mapping;

	for(xml_node<> *map_node = root_node->first_node("map")->first_node(); map_node; map_node = map_node->next_sibling())
	{
		vector<attribut> tmpvect;

		for(xml_attribute<char> *attribute = map_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{ 
			attribut tmpattr;
			tmpattr.name = attribute->name();
			tmpattr.value = attribute->value();

			tmpvect.push_back(tmpattr);

			//cout << "Setting : "  << attribute->name() << " : " << attribute->value() << endl;
		}

		mapping[map_node->name()] = tmpvect;
	}

	for(xml_node<> *binds_nodes = root_node->first_node("binds")->first_node(); binds_nodes; binds_nodes = binds_nodes->next_sibling())
	{
		cout << "Bind : " << binds_nodes->first_attribute()->value() << " : " << binds_nodes->value() << endl;
	}
}