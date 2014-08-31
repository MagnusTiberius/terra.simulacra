

#include "SharedMemory.h"

namespace bbg{

	SharedMemory::SharedMemory( LONG lSize, LPCTSTR lpName, 
									   LPSECURITY_ATTRIBUTES lpSharedMemoryAttributes) : 
																		m_lpSharedMemory(NULL),
																		m_bIsCreator(FALSE),
																		m_dwStatus(NO_ERROR) {
		m_hMapping = ::CreateFileMapping( (HANDLE) 0xFFFFFFFF, lpSharedMemoryAttributes, PAGE_READWRITE, 0, lSize, lpName);
		if (IsValidHandle(m_hMapping)) {
			m_dwStatus = GetLastError();
			if (m_dwStatus == ERROR_ALREADY_EXISTS) {
				m_bIsCreator = FALSE;
			}
			else {
				m_bIsCreator = TRUE;
			}
		}
		else {
			m_dwStatus = ::GetLastError();
		}
		m_lpSharedMemory = (void *) ::MapViewOfFile( m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (m_lpSharedMemory == NULL) {
			m_dwStatus = ::GetLastError();
		}
	}

	SharedMemory::SharedMemory( LPCTSTR lpName) : m_lpSharedMemory(NULL),
																	  m_bIsCreator(FALSE),
																	  m_dwStatus(NO_ERROR) {
		m_hMapping = ::OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, lpName);
		if (IsValidHandle(m_hMapping)) {
			m_dwStatus = NO_ERROR;
		}
		else {
			m_dwStatus = ::GetLastError();
			return;
		}
		m_lpSharedMemory = (void *) ::MapViewOfFile( m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
		if (m_lpSharedMemory == NULL) {
			m_dwStatus = ::GetLastError();
		}
	}
    
	SharedMemory::~SharedMemory() {
		if (m_lpSharedMemory) {
			::UnmapViewOfFile(m_lpSharedMemory);
			m_lpSharedMemory = NULL;
		}
		if (m_hMapping) {
			::CloseHandle(m_hMapping);
		}
	}

	DWORD SharedMemory::Status(void) const {
		return m_dwStatus;
	}

	void * SharedMemory::GetPtr(void) {
		return m_lpSharedMemory;
	}

	BOOL SharedMemory::IsCreator(void) {
		return m_bIsCreator;
	}

}