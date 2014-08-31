#include "Semaphore.h"

namespace bbg{

	Semaphore::Semaphore(void)
	{
	}


	Semaphore::~Semaphore(void)
	{
	}

	Semaphore::Semaphore(int nInitialCount, int nMaximumCount, LPCWSTR lpName, LPSECURITY_ATTRIBUTES lpSemAttributes)
	{
		m_hHandle = ::CreateSemaphore(lpSemAttributes, nInitialCount, nMaximumCount, lpName);
		if (IsValidHandle(m_hHandle))
		{
			if (lpName)
			{
				m_dwStatus = GetLastError();
			}
			else
			{
				m_dwStatus = NO_ERROR;
			}
		}
		else
		{
			m_dwStatus = GetLastError();
		}
	}

	Semaphore::Semaphore(LPCWSTR lpName, BOOL bInheritHandle, DWORD dwDesiredAccess)
	{
		m_hHandle = ::OpenSemaphore(dwDesiredAccess, bInheritHandle, lpName);
		if (IsValidHandle(m_hHandle))
		{
			if (lpName)
			{
				m_dwStatus = GetLastError();
			}
			else
			{
				m_dwStatus = NO_ERROR;
			}
		}
		else
		{
			m_dwStatus = GetLastError();
		}
	}

	BOOL Semaphore::Release(LONG lReleaseCount, LONG* plPreviousCount)
	{
		LONG lPreviousCount;
		BOOL bStatus = ::ReleaseSemaphore(m_hHandle, lReleaseCount, &lPreviousCount);
		if (bStatus && plPreviousCount)
		{
			*plPreviousCount = lPreviousCount;
		}
		return bStatus;
	}

}