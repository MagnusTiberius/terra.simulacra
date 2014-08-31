#pragma once

#include "Global.h"

namespace bbg{

	class CriticalSection
	{
	private:
		CRITICAL_SECTION m_CritSec;
	public:
		CriticalSection();
		~CriticalSection();
		void Enter(void);
		void Leave(void);
		CRITICAL_SECTION* GetCritSec(void);
	};

}