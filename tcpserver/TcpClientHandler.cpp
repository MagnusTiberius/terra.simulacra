
#include "TcpClientHandler.h"

TcpClientHandler::TcpClientHandler()
{
}
TcpClientHandler::TcpClientHandler(SOCKET socket)
{
	TcpClientHandler();
	m_socket = socket;
}
TcpClientHandler::~TcpClientHandler()
{
}

bool TcpClientHandler::IsDone(void)
{
	return isDone;
}

unsigned TcpClientHandler::ThreadHandlerProc(void)
{
	CommandManager* commandManager = CommandManager::Instance();
	requestDataManager = QueueManager<RequestData>::Instance();
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;
	auto boardManager = bbg::BoardManager::Instance();
	isDone = false;
	while ( true ) 
	{
		printf("[0x%08lx] Going for receive...\n", GetCurrentThreadId());
		iResult = recv(m_socket, recvbuf, recvbuflen, 0);
		if (iResult > 0) 
		{
			char* sbuf = (char*)malloc(sizeof(char)*iResult);
			memset(sbuf,0,iResult);
			memcpy(sbuf,&recvbuf[0],iResult);
			std::vector<string> listReceive = bbg::Util::GatherMessages(sbuf,iResult);
			int ctr = 0;
			for(auto itm : listReceive)
			{
				ctr++;
				auto requestData = new bbg::RequestData();
				std::string ssbuf(sbuf);
				requestData->SetMessageData(itm);
				requestData->SetSocket((int)m_socket);
				printf("[0x%08lx] Data Pushed: [socket=%d] [thread=%d] [loop=%d] %s  \n", GetCurrentThreadId() ,
						(int)m_socket, GetCurrentThreadId(), ctr, itm.c_str());
				requestDataManager->GrantWriterAccessEx();
				requestDataManager->AddRequestData(requestData);
				requestDataManager->ReleaseWriterAccessEx();
			}
		}
		if (iResult > 0) 
		{
			printf("[0x%08lx] Bytes received: %d\n", GetCurrentThreadId(), iResult);
			//std::vector<string> s = bbg::Util::Parse(recvbuf, " ",iResult);

			//std::string action = s[0];
			//std::string loginId = "";
			//std::string sayMesg = "";
			//if (action.compare("LOGIN") == 0)
			//{
			//	loginId = s[1];
			//	printf("Login command: %s\n", loginId.c_str());
			//	bbg::User* user = new bbg::User();
			//	user->SetLoginId(loginId);
			//	boardManager->Create(user);
			//}
			//if (action.compare("SAY") == 0)
			//{
			//	loginId = s[1];
			//	sayMesg = s[2];
			//	printf("[0x%08lx] Say command: user %s said \"%s\"\n", GetCurrentThreadId(), loginId.c_str(), sayMesg.c_str());
			//}
			//if (action.compare("QUIT") == 0)
			//{
			//	printf("Quit command: user %s \n", loginId.c_str());
			//	isDone = true;
			//}
			//if (action.compare("SHUTDOWN") == 0)
			//{
			//	isDone = true;
			//	printf("Server shutting down... \n");
			//}
		}
		else if (iResult == 0)
		{
			printf("Zero recv...\n");
			isDone = true;
			closesocket(m_socket);
			return 0;
		}
		else  
		{
			printf("recv() failed with error: %d\n", WSAGetLastError());
			int errCode = WSAGetLastError();
			if (errCode==10054)
			{
				printf("10054 WSAECONNRESET: Connection reset by peer. Client disconnect.\n");
			}
			else if (errCode==10058)
			{
				printf("10058 WSAESHUTDOWN : Cannot send after socket shutdown.\n");
			}
			else if (errCode==10024)
			{
				printf("10024 WSAEMFILE : Too many open files. Too many open sockets. \n");
			}
			else if (errCode==10048)
			{
				printf("10048 WSAEADDRINUSE : Address already in use. \n");
			}
			else if (errCode==10050)
			{
				printf("10050 WSAENETDOWN : Network is down. \n");
			}
			else if (errCode==10051)
			{
				printf("10051 WSAENETUNREACH : Network is unreachable.\n");
			}
			else if (errCode==10052)
			{
				printf("10052 WSAENETRESET : Network dropped connection on reset.\n");
			}
			else if (errCode==10055)
			{
				printf("10055 WSAENOBUFS : No buffer space available.\n");
			}
			else if (errCode==10057)
			{
				printf("10057 WSAENOTCONN : Socket is not connected.\n");
			}
			else if (errCode==10059)
			{
				printf("10059 WSAETOOMANYREFS : Too many references.\n");
			}
			else if (errCode==10060)
			{
				printf("10060 WSAETIMEDOUT : Connection timed out.\n");
			}
			else if (errCode==10061)
			{
				printf("10061 WSAECONNREFUSED : Connection refused.\n");
			}
			else
			{
				printf("XXXXX UNDEFINED : Undefined error code / condition.\n");
			}
			closesocket(m_socket);
			isDone = true;
			break;
		}
		if (iResult == 0 || iResult == -1)
		{
			printf("Socket shutdown...\n");
			iResult = shutdown(m_socket, 1);
			if (iResult == SOCKET_ERROR) {
				printf("shutdown failed with error: %d\n", WSAGetLastError());
				closesocket(m_socket);
				isDone = true;
			}
			printf("Handler exiting...\n");
			return 0;
		}
	} 
	return 0;}