#include "Socket.h"

namespace bbg {

Socket::Socket() {}

Socket::Socket(SOCKET socket)
{
	ConnectSocket = socket;
}

Socket::Socket(std::wstring domain, int port)
{
	printf("Original available port #%d \n", port);
	int findAvailablePort = port;
	//while (!IsPortAvailable(domain, findAvailablePort))
	//{
	//	findAvailablePort++;
	//	printf("Trying port #%d \n", findAvailablePort);
	//}
	printf("Found available port #%d \n", findAvailablePort);

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}
	
	m_currentPort = findAvailablePort;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	PCSTR m_port = (PCSTR)findAvailablePort;
	std::string addr(domain.begin(), domain.end());
	// Resolve the server address and port
	iResult = getaddrinfo(addr.c_str(), m_port, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}
	return;
}


Socket::~Socket(void)
{
	closesocket(ConnectSocket);
	WSACleanup();
}

int Socket::ConnectToServer()
{
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	return 0;
}

bool Socket::IsPortAvailable(std::wstring domain, int port)
{
	// Initialize Winsock
	int iStartUpResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iStartUpResult != 0) {
		printf("WSAStartup failed with error: %d\n", iStartUpResult);
		return false;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	PCSTR m_port = DEFAULT_PORT;
	m_port = (PCSTR)port;
	std::string addr(domain.begin(), domain.end());
	// Resolve the server address and port
	int iAddInfoResult = getaddrinfo(addr.c_str(), m_port, &hints, &result);
	if (iAddInfoResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iAddInfoResult);
		freeaddrinfo(result);
		return false;
	}
	//ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	//if (ListenSocket == INVALID_SOCKET) {
	//	printf("socket failed with error: %ld\n", WSAGetLastError());
	//	freeaddrinfo(result);
	//	return false;
	//}

	//iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	//if (iResult == SOCKET_ERROR) {
	//	printf("bind failed with error: %d\n", WSAGetLastError());
	//	freeaddrinfo(result);
	//	closesocket(ListenSocket);
	//	return false;
	//}

	freeaddrinfo(result);
	closesocket(ListenSocket);
	return true;

}

SOCKET Socket::GetClientSocket()
{
	return ConnectSocket;
}

int Socket::Send(char* buffer)
{
	//int sz = strlen(buffer)+1;
	//char* sbuf = (char*)malloc(sz);
	//memset(sbuf,0,sz);
	//memcpy(sbuf, buffer, strlen(buffer));
	iResult = send(ConnectSocket, buffer, (int)strlen(buffer), 0);
	return iResult;
}

int Socket::Shutdown()
{
	iResult = shutdown(ConnectSocket, SD_SEND);
	return iResult;
}

int Socket::Receive(char* recvbuf, int recvbuflen)
{
	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	return iResult;
}

int Socket::Listen()
{
	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	int iOptVal = 400;
    int iOptLen = sizeof (int);

	iResult = getsockopt(ListenSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &iOptVal, &iOptLen);
	return 0;
}

SOCKET Socket::Accept(void)
{
	ClientSocket = accept(ListenSocket, NULL, NULL);
	return ClientSocket;
}

}