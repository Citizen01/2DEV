#include	<iostream>
#include	<fstream>
#include	<vector>
#include	<string.h>
#include	<stdio.h>

#include	"rapidxml.hpp"

using namespace std;
using namespace rapidxml;

int main(void)
{
	xml_document<> doc;
	xml_node<> *root_node;
	ifstream coreConfig("coreconfig.xml");
	vector<char> buffer((istreambuf_iterator<char>(coreConfig)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	/*parser le buffer avec le fichier xml*/
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node();
	cout <<"Pas dans la boucle \n"<<endl;
	xml_attribute<> *pAttr = root_node->first_attribute();

	for(xml_node<> *mainconfig_node = root_node->first_node(); mainconfig_node; mainconfig_node = mainconfig_node->next_sibling())
	{
		cout <<"dans la boucle \n"<<endl;
		cout << mainconfig_node << endl;
		for(xml_node<> *settings_node = mainconfig_node->first_node("settings"); settings_node; settings_node = settings_node->next_sibling())
		{
			cout << settings_node << endl;
		}
		for(xml_node<> *binds_node = mainconfig_node->first_node("binds"); binds_node; binds_node = binds_node->next_sibling())
		{
			pAttr = root_node->first_attribute("control");
			cout << pAttr << endl;
		}
		for(xml_node<> *updater_node = mainconfig_node->first_node("updater"); updater_node; updater_node = updater_node->next_sibling())
		{
			cout << updater_node << endl;
		}
	}
	system("PAUSE");
}