#include "stdafx.h"
#include "CppUnitTest.h"

#include "SocketServer.h"
#include "Socket.h"

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

	};
}