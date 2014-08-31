#pragma once
#include "Global.h"
#include "CriticalSection.h"
#include "Mutex.h"

namespace bbg{

	class AutoLock
	{
	public:
		AutoLock(void);
		~AutoLock(void);
	private:
		HANDLE m_hMutexHandle;
		CRITICAL_SECTION* m_pCritSec;
		CriticalSection* m_pcCritSec;
		Mutex* m_pcMutex;
	public:
		AutoLock( HANDLE hMutexHandle );
		AutoLock( Mutex& pcMutex );
		AutoLock( CRITICAL_SECTION* pCritSec );
		AutoLock( CriticalSection* pcCritSec );
	};

}