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
			//printf("Data pulled: nothing\n");
		}
		else
		{
			//printf("Data pulled [%lu]: %s\n", (long)m_tid, rd.GetMessageData().c_str());
			std::cout << "Data pulled [thread=" << GetCurrentThreadId() << "] : " << rd.GetMessageData().c_str() << "\n";
		}
		std::chrono::milliseconds dura( 10 );
		std::this_thread::sleep_for( dura );
	}
	printf("BroadcastHandler::ThreadHandlerProc exiting...\n");
	return 0;
}

}