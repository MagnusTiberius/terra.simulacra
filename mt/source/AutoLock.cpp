#include "AutoLock.h"

namespace bbg{

	AutoLock::AutoLock(void)
	{
	}


	AutoLock::~AutoLock(void)
	{
		BOOL bStatus = TRUE;
		if (m_hMutexHandle)
		{
			bStatus = ::ReleaseMutex(m_hMutexHandle);
		}
		else if (m_pcMutex) 
		{
			bStatus = m_pcMutex->Release();
	}
		else if (m_pCritSec)
		{
			::LeaveCriticalSection(m_pCritSec);
		} 
		else 
		{
			m_pcCritSec->Leave();
		}
	}

	AutoLock::AutoLock( HANDLE hMutexHandle )
	{
		m_hMutexHandle = hMutexHandle;
		m_pcMutex = NULL;
		m_pCritSec = NULL;
		m_pcCritSec = NULL;
		::WaitForSingleObject(hMutexHandle, INFINITE);
	}

	AutoLock::AutoLock( Mutex& pcMutex )
	{
		m_hMutexHandle = NULL;
		m_pcMutex = &pcMutex;
		m_pCritSec = NULL;
		m_pcCritSec = NULL;
		m_pcMutex->Wait(INFINITE);
	}

	AutoLock::AutoLock( CRITICAL_SECTION* pCritSec )
	{
		m_hMutexHandle = NULL;
		m_pcMutex = NULL;
		m_pCritSec = pCritSec;
		m_pcCritSec = NULL;
		::EnterCriticalSection(pCritSec);
	}

	AutoLock::AutoLock( CriticalSection* pcCritSec )
	{
		m_hMutexHandle = NULL;
		m_pcMutex = NULL;
		m_pCritSec = NULL;
		m_pcCritSec = pcCritSec;
		pcCritSec->Enter();
	}


}