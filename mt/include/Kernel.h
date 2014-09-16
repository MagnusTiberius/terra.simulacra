#pragma once

#include "WaitableObject.h"
#include "Global.h"
#include <thread>
#include <windows.h>

namespace bbg{

	class Kernel : public WaitableObject
	{
	protected:
		HANDLE m_hHandle;
		DWORD m_dwStatus;
		Kernel();
		void ThrowError(DWORD dwStatus);
	public:
		virtual ~Kernel() = 0;
		DWORD Status(void) const;
		DWORD Wait(DWORD dwMilliseconds);
		DWORD WaitForTwo(WaitableObject &rWaitableObject, bool bWaitAll, DWORD dwMilliseconds);
		DWORD WaitForThree(WaitableObject &rWaitableObject, WaitableObject &rWaitableObject2, bool bWaitAll, DWORD dwMilliseconds);
		HANDLE GetHandle(void) const;
		operator HANDLE() const;
	};

}