#include "Client.h"

void CreateConnection(cSOCKET* sock, const char* ip, const int* port)
{
	if (!ip)
	{
                printf("Ip not set\n");
		return;
	}

	if (!port)
	{
                printf("Port not set\n");
		return;
	}

#ifdef _WIN32
	InitializeWinSock();
#endif

	struct sockaddr_in sockAddr;
	CreateAddrData(&sockAddr, ip, port);

	CreateSockAndConnectToServer(&sockAddr, sock);
}

#ifdef _WIN32
void InitializeWinSock()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		printf("Initializing failed\n");
}
#endif

void CreateAddrData(struct sockaddr_in *sockAddr, const char* ip, const int* port)
{
	sockAddr->sin_family = AF_INET;
	sockAddr->sin_port = htons(*port);
	sockAddr->sin_addr.s_addr = inet_addr(ip);
}

void CreateSockAndConnectToServer(struct sockaddr_in* sockAddr, cSOCKET* sock)
{
	*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == *sock)
		printf("Socket failed\n");

	if (SOCKET_ERROR != connect(*sock, (struct sockaddr*)sockAddr, sizeof(*sockAddr)))
		printf("Connection succeded\n");
	else
		printf("Connection failed\n");
}

void SendMsg(cSOCKET* sock, char* mess)
{
	if (SOCKET_ERROR == send(*sock, mess, DEFAULT_BUFLEN, 0))
		printf("Sending message failed\n");
}

void ReceiveMsg(cSOCKET* sock, char* mess)
{
	if (!recv(*sock, mess, DEFAULT_BUFLEN, 0))
		printf("Receiving message failed\n");
}
