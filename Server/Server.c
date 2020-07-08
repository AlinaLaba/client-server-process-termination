#include "Server.h"

void CreateConnection(cSOCKET* ClientSock)
{
#ifdef _WIN32
	InitializeWinSock();
#endif

	struct sockaddr_in sockAddr;
	CreateAddrData(&sockAddr);

	cSOCKET sock = INVALID_SOCKET;

	CreateSocket(&sockAddr, &sock);

	BindSocket(&sockAddr, &sock);

	ListenSocket(&sock);

	AcceptConnection(&sock, ClientSock);
}

#ifdef _WIN32
void InitializeWinSock()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		printf("Initializing failed\n");
}
#endif

void CreateAddrData(struct sockaddr_in* sockAddr)
{
	sockAddr->sin_family = AF_INET;
	sockAddr->sin_port = htons(DEFAULT_PORT);
	sockAddr->sin_addr.s_addr = INADDR_ANY;
}

void CreateSocket(struct sockaddr_in* sockAddr, cSOCKET* sock)
{
	*sock = socket(sockAddr->sin_family, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == *sock)
		printf("Socket creation failed\n");
}

void BindSocket(struct sockaddr_in* sockAddr, cSOCKET* sock)
{
	if (SOCKET_ERROR == bind(*sock, (struct sockaddr*)(sockAddr), sizeof(*sockAddr)))
		printf("Binding failed\n");
}

void ListenSocket(cSOCKET* sock)
{
	if (SOCKET_ERROR == listen(*sock, SOMAXCONN))
		printf("Listening failed\n");
}

void AcceptConnection(cSOCKET* sock, cSOCKET* ClientSock)
{
	struct sockaddr_in cliAddr;
	int addrlen = sizeof(cliAddr);
	*ClientSock = accept(*sock, (struct sockaddr*)&cliAddr, &addrlen);

	if (INVALID_SOCKET == *ClientSock)
		printf("Accepting connection failed\n");
}

bool ReceiveMsg(cSOCKET* ClientSock, char* mess)
{
	if (recv(*ClientSock, mess, DEFAULT_BUFLEN, 0) > 0)
		return True;

	printf("Receiving message failed\n");
	return False;
}

void SendMsg(cSOCKET* ClientSock, char* mess)
{
	if (SOCKET_ERROR == send(*ClientSock, mess, DEFAULT_BUFLEN, 0))
		printf("Sending message failed\n");
}
