#include "TaskThreadHandler.h"

namespace bbg {

TaskThreadHandler::TaskThreadHandler(void)
{
}


TaskThreadHandler::~TaskThreadHandler(void)
{
}


unsigned TaskThreadHandler::ThreadHandlerProc(void)
{
	printf("[0x%08lx] Thread is starting.  \n", GetCurrentThreadId() );
	srand(GetCurrentThreadId());
	DWORD dwWorkPeriod = (1000 + (rand() % 1000));
	::Sleep(dwWorkPeriod);
	printf("[0x%08lx] Thread is done executing.  Returning to the pool or exiting.\n", GetCurrentThreadId() );
	return 0;
}

}