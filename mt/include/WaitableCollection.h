#pragma once

#include "Global.h"
#include "WaitableObject.h"

namespace bbg{

	class WaitableCollection
	{
	public:
		WaitableCollection(void);
		virtual ~WaitableCollection(void);
	private:
		HANDLE m_aObjectHandles[MAXIMUM_WAIT_OBJECTS];
		LONG m_lObjects;
	public:
		WaitableCollection(WaitableCollection & rhs);
		WaitableCollection & operator= (WaitableCollection & rhs);
		LONG GetCount(void) const;
		BOOL AddObject(const WaitableObject *pObject);
		BOOL AddObject(const WaitableObject & rObject);
		BOOL AddObject(const HANDLE hHandle);
		BOOL AddCollection(const WaitableCollection & rCollection);
		DWORD Wait( BOOL bWaitAll, DWORD dwMilliseconds) const;
	};

}