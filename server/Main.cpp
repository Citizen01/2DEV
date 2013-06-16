#include "server.h"

using namespace std;

int main(void)
{
	Server::getSingleton()->run();

	return 0;
}
