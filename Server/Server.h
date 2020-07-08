#pragma once

#include "ServerTypes.h"
#include <stdio.h>
#define DEFAULT_PORT 24042
#define DEFAULT_BUFLEN 1024

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")

void InitializeWinSock();
#endif

void CreateConnection(cSOCKET* sock);

void CreateAddrData(struct sockaddr_in* sockAddr);

void CreateSocket(struct sockaddr_in* sockAddr, cSOCKET* sock);

void BindSocket(struct sockaddr_in* sockAddr, cSOCKET* sock);

void ListenSocket(cSOCKET* sock);

void AcceptConnection(cSOCKET* sock, cSOCKET* ClientSock);

bool ReceiveMsg(cSOCKET* ClientSock, char* mess);

void SendMsg(cSOCKET* ClientSock, char* mess);