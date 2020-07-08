#pragma once

#include "ClientTypes.h"
#include <stdio.h>

#define DEFAULT_BUFLEN 1024
#define DEFAULT_DOTQUAN 3

struct ConnDetails
{
	char ip[16];
	int port;
};

bool IpIsValid(const char* ip);

void GetConnectionDetails(struct ConnDetails* obj);

bool GetStartingMsg(pReceiveMsg ReceiveMsgPtr, cSOCKET* sock);