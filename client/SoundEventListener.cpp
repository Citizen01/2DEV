#include "SoundEventListener.h"
#include <iostream>

using namespace std;

SoundEventListener::SoundEventListener(void)
{
}


SoundEventListener::~SoundEventListener(void)
{
}

bool SoundEventListener::OnEvent(const irr::SEvent& event)
{
	//Handle events here:
	
	cout << "s "; //preuve de la réception des events

	return false;
}
