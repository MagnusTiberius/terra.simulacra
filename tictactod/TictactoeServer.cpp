#include "TictactoeServer.h"


TictactoeServer::TictactoeServer(void)
	:SocketServer(DEFAULT_DOMAIN, (int)DEFAULT_PORT)
{
}


TictactoeServer::~TictactoeServer(void)
{
}

TictactodThread* TictactoeServer::ReuseThread(void)
{
	for(auto thd : m_ThreadList)
	{
		TictactodThread* t1 = thd.second;
		std::string s2 = thd.first;
		if (t1->isHandlerDone())
		{
			return t1;
		}
	}
	return NULL;
}

void TictactoeServer::Start(void)
{
	auto ref = BoardManager::Instance();
	ref->Init();
	do {
		printf("Listening...\n");
		SOCKET clientSocket = Accept();
		printf("SOCKET # %d...\n", clientSocket);
		TictactodThread* t = ReuseThread();
		if (t != NULL)
		{
			printf("Reusing thread...\n");
			t->SetSocket(clientSocket);
		}
		else
		{
			printf("Creating thread...\n");
			t = TictactodThread::Create(clientSocket);
			char* nm = (char*)malloc(20);
			Util::GenerateRandomChars(nm, 20);
			nm[19]=0;
			std::string s(nm);
			m_ThreadList.insert(std::pair<std::string, TictactodThread*>(s,t));
		}
		auto w = t->Wait(1);
		//for(auto thd : m_ThreadList)
		//{
		//	TictactodThread* t1 = thd.second;
		//	std::string s2 = thd.first;
		//	if (t1)
		//	{
		//		if (t1->isSocketOpen())
		//		{
		//			printf("Socket is open...\n");
		//		}
		//		else
		//		{
		//			printf("Socket is closed...\n");
		//			//t1->Terminate(1);
		//		}

		//		//w = t1->Wait(1);
		//		//if (t1->isHandlerDone())
		//		//{
		//		//	auto itr = m_ThreadList.find(s2);
		//		//	m_ThreadList.erase(itr);
		//		//	delete t1;
		//		//}
		//	}
		//}
		printf("m_ThreadList size...%d\n", m_ThreadList.size());
	} while (true);
}