#include "ClientUI.h"

bool IpIsValid(const char* ip)
{
	int counter = 0;
	for (int i = 0; i < strlen(ip); ++i)
	{
		if (ip[i] == '.')
			counter++;
		if (!isdigit(ip[i]) && ip[i] != '.')
			return False;
	}

	if (DEFAULT_DOTQUAN == counter)
		return True;

	return False;
}

bool PortIsValid(const char* port)
{
	for (int i = 0; i < strlen(port); ++i)
		if (!isdigit(port[i]))
			return False;

	return True;
}

void GetConnectionDetails(struct ConnDetails* obj)
{
	do {
		printf("Input IP adress you want to connect (***.***.***.***): ");
		scanf("%s", obj->ip);

		if (!IpIsValid(obj->ip))
			printf("Wrong IP. Try again\n");
		else
			break;

	} while (True);

	char tmp[10] = { 0 };
	do
	{
		printf("Input port: ");
		scanf("%s", tmp);

		if (!PortIsValid(tmp))
			printf("Wrong port. Try again\n");
		else
		{
			obj->port = atoi(tmp);
			break;
		}

	} while (True);
}

bool GetStartingMsg(pReceiveMsg ReceiveMsgPtr, cSOCKET* sock)
{
	char mess[DEFAULT_BUFLEN] = "\0";
	ReceiveMsgPtr(sock, mess);
	if (!strcmp(mess, "Start\n"))
		return True;
	else
		printf("Starting message receiving failed\n");

	return False;
}
