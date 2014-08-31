#pragma once
#include "Global.h"
#include "Kernel.h"

namespace bbg{

	class Mutex: public Kernel
	{
	public:
		Mutex(BOOL bInitialOwner = FALSE, LPCWSTR lpName = NULL, LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL);
		Mutex(LPCWSTR lpName, BOOL bInheritanceHandle = FALSE, DWORD dwDesiredAccess = MUTEX_ALL_ACCESS);
		~Mutex(void);
		BOOL Release(void);
	};

}