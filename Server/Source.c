#include "Server.h"
#include "ServerUI.h"

int main()
{
	cSOCKET ClientSock = INVALID_SOCKET;
	CreateConnection(&ClientSock);

	StartMenu(SendMsg, &ClientSock);

	ShowProcessList(ReceiveMsg, &ClientSock);

	TerminationMenu(SendMsg, ReceiveMsg, &ClientSock);

#ifdef _WIN32
	system("pause");
#endif
}