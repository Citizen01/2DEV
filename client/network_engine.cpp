#include "application.h"
#include <iostream>

using namespace std;

network_engine::network_engine(Application* ap) : engine(ap)
{

}

network_engine::~network_engine(void)
{
}

//Impl�mentation de la m�thode virtuelle pure h�rit�e de la classe engine
void network_engine::frame()
{
	//Do stuff
}

bool network_engine::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	return false;
}
