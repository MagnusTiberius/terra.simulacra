#include "SocketdHandler.h"
#include "User.h"

SocketdHandler::SocketdHandler(SOCKET clientSocket):
		ThreadHandler()
{
	m_clientSocket = clientSocket;
}


SocketdHandler::~SocketdHandler()
{
}


unsigned SocketdHandler::ThreadHandlerProc(void)
{
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;
	isDone = false;
	auto boardManager = bbg::BoardManager::Instance();

	do {
		iResult = recv(m_clientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			std::vector<string> s = bbg::Util::Parse(recvbuf, " ",iResult);

			std::string action = s[0];
			std::string loginId = "";
			std::string sayMesg = "";
			if (action.compare("LOGIN") == 0)
			{
				loginId = s[1];
				printf("Login command: %s\n", loginId.c_str());
				bbg::User* user = new bbg::User();
				user->SetLoginId(loginId);
				boardManager->Create(user);
			}
			if (action.compare("SAY") == 0)
			{
				loginId = s[1];
				sayMesg = s[2];
				printf("Say command: user %s said \"%s\"\n", loginId.c_str(), sayMesg.c_str());
			}
			if (action.compare("QUIT") == 0)
			{
				printf("Quit command: user %s \n", loginId.c_str());
			}
			// Echo the buffer back to the sender
			int iSendResult = send(m_clientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(m_clientSocket);
				WSACleanup();
				break;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else  {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(m_clientSocket);
			WSACleanup();
			break;
		}

	} while (iResult > 0);

	printf("Thread closing...\n");
	// shutdown the connection since we're done
	iResult = shutdown(m_clientSocket, 1);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(m_clientSocket);
		WSACleanup();
		return 1;
	}
	isDone = true;
	return 1;
}