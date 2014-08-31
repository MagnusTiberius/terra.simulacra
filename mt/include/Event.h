#pragma once

#include "Global.h"
#include "Kernel.h"

namespace bbg{

	class Event: public Kernel
	{
	public:
		~Event(void);
		Event(BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, LPCTSTR lpName = NULL, LPSECURITY_ATTRIBUTES lpEventAttributes = NULL);
		Event( LPCTSTR lpName, BOOL bInheritHandle = FALSE, DWORD dwDesiredAccess = EVENT_ALL_ACCESS);
		BOOL Set(void);
		BOOL Reset(void);
		BOOL Pulse(void);
	private:
		//Event(void);
	};

}