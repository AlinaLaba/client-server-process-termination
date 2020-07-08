#include "ProcessManager.h"

#ifdef _WIN32
void GetProcessList(pSendList SendListPtr, cSOCKET* sock)
{
	char buffer[DEFAULT_BUFLEN] = { 0 }, buf[10];
	unsigned counter = 0;

	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnapshot)
		printf("Process snapshot creating failed\n");

	PROCESSENTRY32 PEntry;
	PEntry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnapshot, &PEntry))
	{
		printf("Process32First failed\n");
		CloseHandle(hProcessSnapshot);
		return;
	}

	do {
		strcat(buffer, "Process Name: ");
		strcat(buffer, PEntry.szExeFile);

		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PEntry.th32ProcessID);
		if (NULL == hProcess)
			strcat(buffer, "\n<<Access denied>>");
		else
			CloseHandle(hProcess);

		strcat(buffer, "\nProcess ID: ");
		_itoa(PEntry.th32ProcessID, buf, 10);
		strcat(buffer, buf);
		strcat(buffer, "\n\n");

		counter++;
		if (DEFAULT_STRINGQUAN == counter)
		{
			SendListPtr(sock, buffer);
			counter = 0;
			memset(buffer, 0, strlen(buffer));
		}
		if (!Process32Next(hProcessSnapshot, &PEntry))
		{
			SendListPtr(sock, buffer);
			return;
		}

	} while (True);

	CloseHandle(hProcessSnapshot);
}

bool KillProcess(int PID)
{
	HANDLE hProcess = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, FALSE, (DWORD)PID);
	return TerminateProcess(hProcess, 0);
}

#elif __linux__

bool isValid(char* buf)
{
	for (int i = 0; i < strlen(buf); ++i)
		if (isalpha(buf[i]))
			return False;
	return True;
}

void GetProcessList(pSendList SendListPtr, cSOCKET* sock)
{
	char buffer[DEFAULT_BUFLEN] = { 0 }, path[100] = { 0 };
	register struct dirent *dirbuf = NULL;
	char* dirname = "/proc";
	DIR *fdir = NULL;
	int counter = 0;

	fdir = opendir(dirname);
	if (!fdir)
	{
		printf("Can't open %s\n", dirname);
		return;
	}

	dirbuf = readdir(fdir);
	do {
		if (!strcmp(dirbuf->d_name, ".") || !strcmp(dirbuf->d_name, "..") || !isValid(dirbuf->d_name))
		{
			dirbuf = readdir(fdir);
			continue;
		}

		strcat(buffer, "Process Name: ");

		strcat(path, "/proc/");
		strcat(path, dirbuf->d_name);
		strcat(path, "/cmdline");

		int fd = open(path, O_RDONLY);
		if (-1 == fd)
			printf("Can't open file %s\n", path);
		else
		{
			char buff[BUFFERSIZE] = "\0";
			read(fd, buff, BUFFERSIZE);
			if (!strlen(buff))
			{
				memset(path, 0, strlen(path) + 1);
				memset(buffer, 0, strlen(path) + 1);
				dirbuf = readdir(fdir);
				continue;
			}
			else
				strcat(buffer, buff);

			close(fd);
		}

		strcat(buffer, "\nProcess ID: ");
		strcat(buffer, dirbuf->d_name);
		strcat(buffer, "\n\n\0");
		memset(path, 0, strlen(path) + 1);

		counter++;
		if (DEFAULT_STRINGQUAN == counter)
		{
			SendListPtr(sock, buffer);
			counter = 0;
			memset(buffer, 0, strlen(buffer));
		}
		if ((dirbuf = readdir(fdir)) == NULL)
		{
			SendListPtr(sock, buffer);
			closedir(fdir);
			return;
		}
	} while (True);
}

bool KillProcess(int PID)
{
	return !kill(PID, SIGTERM);
}

#endif
