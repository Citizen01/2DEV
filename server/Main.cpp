#include "server.h"

using namespace std;

int main(void)
{
	return Server::GetSingleton()->Run();
}
