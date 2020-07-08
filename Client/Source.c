#include "Client.h"
#include "ProcessManager.h"
#include "ClientUI.h"

int main()
{
	cSOCKET sock = INVALID_SOCKET;

	struct ConnDetails obj;
	GetConnectionDetails(&obj);
	CreateConnection(&sock, obj.ip, &obj.port);
	char mess[DEFAULT_BUFLEN] = { 0 };

	if (GetStartingMsg(ReceiveMsg, &sock))
	{
		void(*SendList)(cSOCKET*, char*);
		SendList = SendMsg;
		GetProcessList(SendList, &sock);
		SendMsg(&sock, (char*)"ENDSENDING");
	}
	else
		printf("Wrong starting message\n");


	ReceiveMsg(&sock, mess);

	if (KillProcess(atoi(mess)))
		SendMsg(&sock, (char*)"Process termination succeded");
	else
		SendMsg(&sock, (char*)"Process termination failed");

#ifdef _WIN32
	system("pause");
#endif
}
