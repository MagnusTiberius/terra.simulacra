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
	DWORD dwWorkPeriod = (1000 + (rand() % 500));
	printf("[0x%08lx] Thread is starting. Sleep val = %d \n", GetCurrentThreadId(), (int)dwWorkPeriod );
	srand(GetCurrentThreadId());
	::Sleep(dwWorkPeriod);
	printf("[0x%08lx] Thread is done executing.  Returning to the pool or exiting.\n", GetCurrentThreadId() );
	return 0;
}

}