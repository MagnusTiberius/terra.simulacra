#include "Mutex.h"

namespace bbg{

	Mutex::Mutex(BOOL bInitialOwner, LPCWSTR lpName, LPSECURITY_ATTRIBUTES lpMutexAttributes)
	{
		m_hHandle = ::CreateMutex(lpMutexAttributes, bInitialOwner, lpName);
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

	Mutex::Mutex(LPCWSTR lpName, BOOL bInheritanceHandle, DWORD dwDesiredAccess)
	{
		m_hHandle = ::OpenMutex(dwDesiredAccess, bInheritanceHandle, lpName);
		if (IsValidHandle(m_hHandle))
		{
			m_dwStatus = NO_ERROR;
		}
		else
		{
			m_dwStatus = GetLastError();
		}
	}

	BOOL Mutex::Release(void)
	{
		return ::ReleaseMutex(m_hHandle);
	}

	Mutex::~Mutex(void)
	{
	}

}