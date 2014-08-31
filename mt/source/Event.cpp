#include "Event.h"

namespace bbg{

	//Event::Event(void)
	//{
	//}


	Event::~Event(void)
	{
	}

	Event::Event(BOOL bManualReset, BOOL bInitialState, LPCTSTR lpName, LPSECURITY_ATTRIBUTES lpEventAttributes)
	{
		m_hHandle = ::CreateEvent(lpEventAttributes, bManualReset, bInitialState, lpName);
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

	Event::Event( LPCTSTR lpName, BOOL bInheritHandle, DWORD dwDesiredAccess)
	{
		m_hHandle = ::OpenEvent(dwDesiredAccess, bInheritHandle, lpName);
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

	BOOL Event::Set(void)
	{
		return ::SetEvent(m_hHandle);
	}
	
	BOOL Event::Reset(void)
	{
		return ::ResetEvent(m_hHandle);
	}

	BOOL Event::Pulse(void)
	{
		return ::PulseEvent(m_hHandle);
	}

}