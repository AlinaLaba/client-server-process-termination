#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>

typedef SOCKET cSOCKET;

#elif __linux__
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef int cSOCKET;

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

typedef void(*pReceiveMsg)(cSOCKET*, char*);

typedef void(pSendList)(cSOCKET*, char*);

typedef unsigned char bool;
static const bool False = 0;
static const bool True = 1;