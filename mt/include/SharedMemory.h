#pragma once

#include "Global.h"

namespace bbg{

	class SharedMemory {
	private:
		void *m_lpSharedMemory;
		HANDLE m_hMapping;
		BOOL m_bIsCreator;
		DWORD m_dwStatus;
	public:
		SharedMemory( LONG lSize, LPCTSTR lpName, LPSECURITY_ATTRIBUTES lpSharedMemoryAttributes = NULL);
		SharedMemory( LPCTSTR lpName);
		virtual ~SharedMemory();
		DWORD Status(void) const;
		void *GetPtr(void);
		BOOL IsCreator(void);
	};
}
