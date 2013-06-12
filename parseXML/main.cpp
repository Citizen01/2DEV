#include	<iostream>
#include	<fstream>
#include	<vector>
#include	<string.h>
#include	<stdio.h>

#include	"rapidxml.hpp"

#include "XMLParser.h"

using namespace std;
using namespace rapidxml;

int main(void)
{
	
	XMLParser parser;
	/*parser.CoreConfig();*/
	parser.populateMap();
	

	system("PAUSE");

	return 0;
}