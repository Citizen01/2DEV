#include "XMLParser.h"

XMLParser::XMLParser()
{
	xml_document<> m_Doc;
}

bool XMLParser::openXML(string fileName)
{
	ifstream file(fileName);
	if(file.fail())
	{
		cout << "oups!"<<endl;
		return false;
	}

	buffer = vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	m_Doc.clear();
	m_Doc.parse<0>(&buffer[0]);

	return true;
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

				cout << "Setting : "  << attribute->name() << " : " << attribute->value() << endl;
			}

			mapping[map_node->name()] = tmpvect;
		}
	}
	return mapping;
}