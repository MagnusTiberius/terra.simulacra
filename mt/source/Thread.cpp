#include "Thread.h"

namespace bbg{

	Thread::Thread(ThreadHandler* pcThreadHandler)
	{
		m_lpThreadHandler = pcThreadHandler;
		m_hHandle = ::CreateThread(NULL, 0, CallThreadHandlerProc, reinterpret_cast<LPVOID>(m_lpThreadHandler), NULL, m_uiThreadID);
	}

	Thread::Thread(void)
	{
		m_hHandle = NULL;
	}

	Thread::~Thread()
	{
		//if (m_lpThreadHandler)
		//	delete m_lpThreadHandler;
		m_lpThreadHandler = NULL;
		m_hHandle = NULL;
	}

	void Thread::SetHandler(ThreadHandler* pcThreadHandler)
	{
		if (m_hHandle != NULL) 
		{
			::TerminateThread(m_hHandle, 1);
		}
		m_lpThreadHandler = pcThreadHandler;
		m_hHandle = ::CreateThread(NULL, 0, CallThreadHandlerProc, reinterpret_cast<LPVOID>(m_lpThreadHandler), NULL, m_uiThreadID);
	}

	DWORD WINAPI Thread::CallThreadHandlerProc(void* pThreadHandler)
	{
		ThreadHandler* pcHandler = reinterpret_cast<ThreadHandler*>(pThreadHandler);
		int v =  pcHandler->ThreadHandlerProc();
		return v;
	}

	DWORD Thread::Suspend(void)
	{
		return ::SuspendThread(m_hHandle);
	}

	DWORD Thread::Resume(void)
	{
		return ::ResumeThread(m_hHandle);
	}

	BOOL Thread::Terminate(DWORD pdwExitCode)
	{
		return ::TerminateThread(m_hHandle, pdwExitCode);
	}

	BOOL Thread::SetPriority(int nPriority)
	{
		return ::SetThreadPriority(m_hHandle, nPriority);
	}

	BOOL Thread::GetExitCode(DWORD* pdwExitCode)
	{
		return ::GetExitCodeThread(m_hHandle, pdwExitCode);
	}

	int Thread::GetPriority(void)
	{
		return ::GetThreadPriority(m_hHandle);
	}

	LPDWORD Thread::GetThreadId(void)
	{
		return m_uiThreadID;
	}
}