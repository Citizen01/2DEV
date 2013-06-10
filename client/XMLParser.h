#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "GLOBALS.h"
#include "rapidxml.hpp"


class XMLParser {
private:
	std::vector<char> buffer;
	rapidxml::xml_document<> m_Doc;

public:
	XMLParser(std::string fileName);
	bool openXML(std::string fileName);
	bool populateSettings(std::map<std::string,std::string> &settings);
	bool populateBind(std::map<constants::ACTION_CODE, irr::EKEY_CODE> &binds);
	~XMLParser();
};