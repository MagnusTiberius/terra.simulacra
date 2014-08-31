#include "Kernel.h"

namespace bbg{

	Kernel::Kernel()
	{
		m_hHandle = NULL;
		m_dwStatus = ERROR_INVALID_HANDLE;
	}


	Kernel::~Kernel()
	{
		if (IsValidHandle(m_hHandle))
		{
			::CloseHandle(m_hHandle);
			m_hHandle = NULL;
		}
	}

	void Kernel::ThrowError(DWORD dwStatus)
	{
		m_hHandle = NULL;
		m_dwStatus = ERROR_INVALID_HANDLE;
	}

	DWORD Kernel::Status(void) const
	{
		return m_dwStatus;
	}

	DWORD Kernel::Wait(DWORD dwMilliseconds)
	{
		return ::WaitForSingleObjectEx(m_hHandle, dwMilliseconds, true);
	}

	DWORD Kernel::WaitForTwo(WaitableObject &rWaitableObject, bool bWaitAll, DWORD dwMilliseconds)
	{
		HANDLE handles[2];
		handles[0] = m_hHandle;
		handles[1] = rWaitableObject.GetHandle();
		return ::WaitForMultipleObjectsEx(2, handles, bWaitAll, dwMilliseconds, true);
	}

	HANDLE Kernel::GetHandle(void) const
	{
		if (this != NULL)
			return m_hHandle;
		else
			return NULL;
	}

	Kernel::operator HANDLE() const
	{
		return GetHandle();
	}

}