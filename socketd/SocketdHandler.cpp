#include "SocketdHandler.h"

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

	do {
		iResult = recv(m_clientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

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