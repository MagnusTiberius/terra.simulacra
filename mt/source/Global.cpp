#include "Global.h"

namespace bbg{

	Global::Global()
	{
	}


	Global::~Global()
	{
	}

	bool IsValidHandle(HANDLE hHandle)
	{
		return ((hHandle != NULL) && (hHandle != INVALID_HANDLE_VALUE));
	}

	bool WaitSucceeded(DWORD dwWaitResult, DWORD dwHandleCount)
	{
		return ((dwWaitResult >= WAIT_OBJECT_0) && 
			(dwWaitResult < WAIT_OBJECT_0 + dwHandleCount));
	}

	bool WaitAbandoned(DWORD dwWaitResult, DWORD dwHandleCount)
	{
		return ((dwWaitResult >= WAIT_ABANDONED_0) &&
			(dwWaitResult < WAIT_ABANDONED_0 + dwHandleCount));
	}

	bool WaitTimeout(DWORD dwWaitResult)
	{
		return (dwWaitResult == WAIT_TIMEOUT);
	}

	bool WaitFailed(DWORD dwWaitResult)
	{
		return (dwWaitResult == WAIT_FAILED);
	}

	bool WaitSucceededIndex(DWORD dwWaitResult)
	{
		return (dwWaitResult == WAIT_OBJECT_0);
	}

	bool WaitAbandonedIndex(DWORD dwWaitResult)
	{
		return (dwWaitResult == WAIT_ABANDONED_0);
	}

}