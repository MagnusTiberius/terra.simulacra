#include "WaitableCollection.h"

namespace bbg{

	WaitableCollection::WaitableCollection(void)
	{
		m_lObjects = 0;
	}


	WaitableCollection::~WaitableCollection(void)
	{
	}


	WaitableCollection::WaitableCollection(WaitableCollection & rhs) {
		*this = rhs;
	}

	WaitableCollection & WaitableCollection::operator= (WaitableCollection & rhs) { 
		for (int i = 0; i < rhs.m_lObjects; i++) {
			m_aObjectHandles[i] = rhs.m_aObjectHandles[i];
		}
		m_lObjects = rhs.m_lObjects;
		return *this; 
	}

	LONG WaitableCollection::GetCount(void) const {
		return m_lObjects;
	}

	BOOL WaitableCollection::AddObject(const WaitableObject *pObject) {
		// make sure that we are not full...
		if (m_lObjects == MAXIMUM_WAIT_OBJECTS)
			return FALSE;

		// add the object's HANDLE to our wait list...
		m_aObjectHandles[m_lObjects++] = pObject->GetHandle();

		return TRUE;
	}

	BOOL WaitableCollection::AddObject(const WaitableObject & rObject) {
		// make sure that we are not full...
		if (m_lObjects == MAXIMUM_WAIT_OBJECTS)
			return FALSE;

		// add the object's HANDLE to our wait list...
		m_aObjectHandles[m_lObjects++] = rObject.GetHandle();

		return TRUE;
	}

	BOOL WaitableCollection::AddObject(const HANDLE hHandle) {
		// make sure that we are not full...
		if (m_lObjects == MAXIMUM_WAIT_OBJECTS)
			return FALSE;

		// add the HANDLE to our wait list...
		m_aObjectHandles[m_lObjects++] = hHandle;

		return TRUE;
	}

	BOOL WaitableCollection::AddCollection( const WaitableCollection & rCollection) {
		for (int i = 0; i < rCollection.m_lObjects; i++) {
			if (!AddObject(rCollection.m_aObjectHandles[i]))
				return FALSE;
		}
		return TRUE;
	}

	DWORD WaitableCollection::Wait( BOOL bWaitAll, DWORD dwMilliseconds) const {
		// check the number of objects...
		if (m_lObjects == 0) {
			return WAIT_FAILED;
		}
    
		// wait for the objects...
		return ::WaitForMultipleObjects( m_lObjects, m_aObjectHandles, bWaitAll, dwMilliseconds);
	}



}