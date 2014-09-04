#pragma once
#include "Global.h"
#include "Kernel.h"
#include "ThreadHandler.h"
#include "windows.h"
#include <thread>

namespace bbg{

	class Thread: public Kernel
	{
	protected:
		LPDWORD m_uiThreadID;
		ThreadHandler* m_lpThreadHandler;
	public:
		~Thread();
		Thread(ThreadHandler* pcThreadHandler);
		DWORD Suspend(void);
		DWORD Resume(void);
		BOOL Terminate(DWORD pdwExitCode);
		BOOL SetPriority(int nPriority);
		int GetPriority(void);
		LPDWORD GetThreadId(void);
		BOOL GetExitCode(DWORD* pdwExitCode);
		void SetHandler(ThreadHandler* pcThreadHandler);
	private:
		Thread(void);
		static DWORD WINAPI CallThreadHandlerProc(void* pThreadHandler);
	};

}