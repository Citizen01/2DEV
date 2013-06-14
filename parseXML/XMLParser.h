#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

struct attribut{
	char* name;
	char* value;
};

class XMLParser {
private:
	vector<char> buffer;
	xml_document<> m_Doc;

public:

	XMLParser(void);
	bool openXML(string fileName);
	/*void CoreConfig();*/
	 map<char*, vector<attribut>> getMapping(string filePath);
};

