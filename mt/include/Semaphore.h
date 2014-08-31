#pragma once

#include "Global.h"
#include "Kernel.h"

namespace bbg{

	class Semaphore: public Kernel
	{
	public:
		Semaphore(int nInitialCount, int nMaximumCount, LPCWSTR lpName = NULL, LPSECURITY_ATTRIBUTES lpSemAttributes = NULL);
		Semaphore(LPCWSTR lpName, BOOL bInheritHandle = FALSE, DWORD dwDesiredAccess = SEMAPHORE_ALL_ACCESS);
		~Semaphore(void);
		BOOL Release(LONG lReleaseCount, LONG* plPreviousCount);
	private:
		Semaphore(void);
	};

}