#pragma once

#include "ClientTypes.h"
#include <stdio.h>
#define DEFAULT_BUFLEN 1024

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")

void InitializeWinSock();
#endif

void CreateAddrData(struct sockaddr_in* addrdata, const char* ip, const int* port);

void CreateSockAndConnectToServer(struct sockaddr_in* addrdata, cSOCKET* sock);

void SendMsg(cSOCKET* sock, char* mess);

void ReceiveMsg(cSOCKET* sock, char* mess);

void CreateConnection(cSOCKET* sock, const char* ip, const int* port);