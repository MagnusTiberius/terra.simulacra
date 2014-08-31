#pragma once
#include "windows.h"
#include <thread>

namespace bbg{

	class Global
	{
	public:
		Global();
		~Global();
	};

	bool IsValidHandle(HANDLE hHandle);
	bool WaitSucceeded(DWORD dwWaitResult, DWORD dwHandleCount);
	bool WaitAbandoned(DWORD dwWaitResult, DWORD dwHandleCount);
	bool WaitTimeout(DWORD dwWaitResult);
	bool WaitFailed(DWORD dwWaitResult);
	bool WaitSucceededIndex(DWORD dwWaitResult);
	bool WaitAbandonedIndex(DWORD dwWaitResult);
}