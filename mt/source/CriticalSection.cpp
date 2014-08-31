#include "CriticalSection.h"

namespace bbg{

	CriticalSection::CriticalSection()
	{
		::InitializeCriticalSection(&m_CritSec);
	}

	CriticalSection::~CriticalSection()
	{
		::DeleteCriticalSection(&m_CritSec);
	}

	void CriticalSection::Enter(void)
	{
		::EnterCriticalSection(&m_CritSec);
	}

	void CriticalSection::Leave(void)
	{
		::LeaveCriticalSection(&m_CritSec);
	}

	CRITICAL_SECTION* CriticalSection::GetCritSec(void)
	{
		return &m_CritSec;
	}

}