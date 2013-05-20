#include "app.h"
#include <iostream>

using namespace std;

network_engine::network_engine(App* ap) : engine(ap)
{

}

network_engine::~network_engine(void)
{
}

//Implémentation de la méthode virtuelle pure héritée de la classe engine
void network_engine::frame()
{
	//Do stuff
}

bool network_engine::OnEvent(const irr::SEvent& event)
{
	//Handle events here:

	return false;
}
