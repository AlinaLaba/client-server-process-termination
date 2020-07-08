#pragma once

#include "ClientTypes.h"
#ifdef _WIN32
#include <tlhelp32.h>
#include <tchar.h>

#elif __linux__
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#endif

#define DEFAULT_BUFLEN 1024
#define DEFAULT_STRINGQUAN 10
#define BUFFERSIZE 1024

void GetProcessList(pSendList SendListPtr, cSOCKET* sock);

bool KillProcess(int PID);
