#pragma once

#include "ServerTypes.h"
#include <stdio.h>

#define DEFAULT_BUFLEN 1024

void StartMenu(pSendMsg SendMsgPtr, cSOCKET* sock);

void ShowProcessList(pReceiveMsg ReceiveMsgPtr, cSOCKET* sock);

void TerminationMenu(pSendMsg SendMsgPtr, pReceiveMsg ReceiveMsgPtr, cSOCKET* sock);