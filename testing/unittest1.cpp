#include "stdafx.h"
#include "CppUnitTest.h"

#include "SocketServer.h"
#include "Socket.h"
#include "Util.h"

#include <string>
#include <vector>

#include "CircularBuffer.h"
#include "RequestData.h"
#include "CircularQueue.h"
#include "QueueManager.h"
#include "ClientSocketHandler.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace bbg;



namespace testing
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			SocketServer s(DEFAULT_DOMAIN, (int)DEFAULT_PORT);
			s.Listen();
			SOCKET socket = s.Accept();
		}

		TEST_METHOD(TestMethod2)
		{
			Socket* s = new Socket (DEFAULT_DOMAIN, (int)DEFAULT_PORT);
		}

		TEST_METHOD(TestMethod3)
		{
			char* buf = "LOGIN john23 ; SAY john23 \"Hello there!\" ;";
			auto list = Util::GatherMessages(buf, strlen(buf));
		}

		TEST_METHOD(TestMethod4)
		{
			char* buf = "LOGIN john23; SAY john23 \"Hello there!\";";
			auto list = Util::GatherMessages(buf, strlen(buf));
		}

		TEST_METHOD(TestMethod5)
		{
			char* buf = "LOGIN john23;";
			auto list = Util::Parse(buf, ";", strlen(buf));
		}

		//TEST_METHOD(TestMethod6)
		//{
		//	CircularBuffer<ElemType> cb;
		//	cb.Init(512);
		//	ElemType et;
		//	et.value = 4;
		//	cb.Write(&et);
		//	ElemType et2;
		//	et2.value=5;
		//	cb.Write(&et2);
		//	ElemType et3;
		//	cb.Read(&et3);
		//	ElemType et4;
		//	cb.Read(&et4);
		//}

		//TEST_METHOD(TestMethod7)
		//{
		//	CircularBuffer<ElemType> cb;
		//	cb.Init(512);
		//	for(int i=0; i<512; i++)
		//	{
		//		ElemType* e = new ElemType();
		//		e->value = i;
		//		cb.Write(e);
		//	}
		//	for(int j=0; j<512; j++)
		//	{
		//		ElemType* f = new ElemType();
		//		cb.Read(f);
		//	}
		//}

		TEST_METHOD(TestMethod8)
		{
			CircularBuffer<RequestData> cb;
			cb.Init(512);
			RequestData* rd0 = new RequestData();
			rd0->SetMessageData("Test1");
			cb.Write(rd0);
			rd0 = new RequestData();
			rd0->SetMessageData("Test2");
			cb.Write(rd0);
			RequestData* rdo1 = new RequestData();
			cb.Read(rdo1);
			RequestData* rdo2 = new RequestData();
			cb.Read(rdo2);
		}

		TEST_METHOD(TestMethod9)
		{
			CircularQueue<RequestData> q;
			RequestData* rd0 = new RequestData();
			rd0->SetMessageData("Test1");
			q.Write(rd0);
			rd0 = new RequestData();
			rd0->SetMessageData("Test2");
			q.Write(rd0);
			RequestData* rdo1 = new RequestData();
			rdo1 = q.Read();
			auto msg = rdo1->GetMessageData();
			rdo1 = q.Read();
			rdo1 = q.Read();
		}

		TEST_METHOD(TestMethod10)
		{
			QueueManager<RequestData>* qm = QueueManager<RequestData>::Instance();
			RequestData* rd0 = new RequestData();
			rd0->SetMessageData("Test1");
			qm->GrantWriterAccess();
			qm->AddRequestData(rd0);
			qm->ReleaseWriterAccess();
			RequestData* rd1 = new RequestData();
			qm->GrantWriterAccess();
			rd1 = qm->ReadRequestData();
			qm->ReleaseWriterAccess();
		}

		TEST_METHOD(TestMethod11)
		{
			ClientSocketHandler* ch = new ClientSocketHandler();
			ch->ThreadHandlerProc();
		}

		TEST_METHOD(TestMethod12)
		{
			ThreadPool threadPool;
			TaskThreadHandler job1;
			threadPool.DispatchThread(&job1);
			TaskThreadHandler job2;
			threadPool.DispatchThread(&job2);
			int n = 0;
			while (threadPool.IsRunning())
			{
				if (n < 100)
				{
					::Sleep(500);
					TaskThreadHandler* moreJobRightHere = new TaskThreadHandler();
					threadPool.DispatchThread(moreJobRightHere);
					n++;
				}
				if (n >= 100)
				{
					threadPool.Shutdown();
				}
			}
			int m = 1;
		}

	};
}