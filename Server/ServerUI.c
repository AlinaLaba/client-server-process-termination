#include "ServerUI.h"

void StartMenu(pSendMsg SendMsgPtr, cSOCKET* sock)
{
	printf("Press '1' to send request to client\n");
	char key = '\0';
	char mess[10] = { 0 };

	do {
		scanf("%c", &key);
		if ('1' == key)
		{
			strcpy(mess, "Start\n");
			break;
		}
		else
			printf("Unknown command. Try again\n");
	} while (True);

	SendMsgPtr(sock, mess);
}

void ShowProcessList(pReceiveMsg ReceiveMsgPtr, cSOCKET* sock)
{
	char buffer[DEFAULT_BUFLEN] = { 0 };

	while (ReceiveMsgPtr(sock, buffer))
	{
		if (strstr(buffer, "ENDSENDING"))
			break;
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}

void TerminationMenu(pSendMsg SendMsgPtr, pReceiveMsg ReceiveMsgPtr, cSOCKET* sock)
{
	char buffer[DEFAULT_BUFLEN] = { 0 };

	for (int i = 0; i < 100; ++i)
		printf("*");

	printf("\nType the Process ID you want to terminate.\n");

	do {
		scanf("%s", buffer);
		if (atoi(buffer))
			break;
	} while (True);

	SendMsgPtr(sock, buffer);

	memset(buffer, 0, sizeof(buffer));
	ReceiveMsgPtr(sock, buffer);
	printf("%s\n", buffer);
}
