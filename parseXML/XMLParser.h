#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class XMLParser {
private:
	vector<char> buffer;
	xml_document<> m_Doc;

public:

	XMLParser(void);
	bool OpenXML(string fileName);
	void CoreConfig(/*Local_Player Player */);
};