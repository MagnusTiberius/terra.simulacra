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

void SocketdHandler::SetSocket(SOCKET socket)
{
	m_clientSocket = socket;
	isDone = false;
}

SOCKET SocketdHandler::GetSocket()
{
	return m_clientSocket;
}

BOOL SocketdHandler::isHandlerDone()
{
	return isDone;
}

void SocketdHandler::SetDone(BOOL bValue)
{
	isDone = bValue;
}

unsigned SocketdHandler::ThreadHandlerProc(void)
{
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;
	auto boardManager = bbg::BoardManager::Instance();

	isDone = false;

	while ( true ) 
	{
		iResult = recv(m_clientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) 
		{
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
				isDone = true;
			}
			if (action.compare("SHUTDOWN") == 0)
			{
				isDone = true;
				printf("Server shutting down... \n");
			}
			// Echo the buffer back to the sender
			int iSendResult = send(m_clientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(m_clientSocket);
				//WSACleanup();
				isDone = true;
				break;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
		{
			printf("Zero recv...\n");
			isDone = true;
			closesocket(m_clientSocket);
			return 0;
		}
		else  
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(m_clientSocket);
			//WSACleanup();
			isDone = true;
			break;
		}


		if (iResult == 0 || iResult == -1)
		{
			printf("Socket shutdown...\n");
			// shutdown the connection since we're done
			iResult = shutdown(m_clientSocket, 1);
			if (iResult == SOCKET_ERROR) {
				printf("shutdown failed with error: %d\n", WSAGetLastError());
				closesocket(m_clientSocket);
				//WSACleanup();
				isDone = true;
			}
			printf("Handler exiting...\n");
			return 0;
		}
	} 
	return 0;
}