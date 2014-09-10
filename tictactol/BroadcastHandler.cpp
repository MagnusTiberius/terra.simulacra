#include "BroadcastHandler.h"


namespace bbg {

BroadcastHandler::BroadcastHandler(void)
{
	handler = RequestDataManager<RequestData>::Instance();
	m_tid = std::this_thread::get_id();
	name = (char*)malloc(sizeof(char)*10);
	Util::GenerateRandomChars(name, 10);
	//std::cout << "Thread Created [" << name << "]  " << "\n";
}


BroadcastHandler::~BroadcastHandler(void)
{
}


unsigned BroadcastHandler::ThreadHandlerProc(void)
{
	RequestData rd;
	while(true)
	{
		rd.SetMessageData("#$#");
		rd.SetUserID("#$#");
		handler->GrantWriterAccess();
		handler->ReadRequestData(&rd);
		handler->ReleaseWriterAccess();
		if (rd.GetMessageData().compare("#$#")==0)
		{
			//std::cout << "Data pulled empty [thread=" << GetCurrentThreadId() << "] : " << "\n";
		}
		else
		{
			//printf("Data pulled [%lu]: %s\n", (long)m_tid, rd.GetMessageData().c_str());
			std::cout << "Data pulled value [thread=" << GetCurrentThreadId() << "] : " << rd.GetMessageData().c_str() << " socket=" << rd.GetSocket() << "\n";
		}
		//std::chrono::milliseconds dura( 1 );
		//std::this_thread::sleep_for( dura );
	}
	printf("BroadcastHandler::ThreadHandlerProc exiting...\n");
	return 0;
}

}