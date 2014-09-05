#include "stdafx.h"
#include "CppUnitTest.h"

#include "SocketServer.h"
#include "Socket.h"
#include "Util.h"

#include <string>
#include <vector>

#include "CircularBuffer.h"

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

		TEST_METHOD(TestMethod6)
		{
			CircularBuffer<ElemType> cb;
			cb.Init(512);
			ElemType et;
			et.value = 4;
			cb.Write(&et);
			ElemType et2;
			et2.value=5;
			cb.Write(&et2);
			ElemType et3;
			cb.Read(&et3);
			ElemType et4;
			cb.Read(&et4);
		}

		TEST_METHOD(TestMethod7)
		{
			CircularBuffer<ElemType> cb;
			cb.Init(512);
			for(int i=0; i<512; i++)
			{
				ElemType* e = new ElemType();
				e->value = i;
				cb.Write(e);
			}
			for(int j=0; j<512; j++)
			{
				ElemType* f = new ElemType();
				cb.Read(f);
			}
		}

	};
}