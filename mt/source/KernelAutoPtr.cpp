#include "KernelAutoPtr.h"

namespace bbg{

	KernelAutoPtr::KernelAutoPtr(Kernel *pObjectPtr) { 
		m_pObjectPtr = pObjectPtr; 
	}

	KernelAutoPtr::~KernelAutoPtr() {
		delete m_pObjectPtr; 
	}

	void KernelAutoPtr::Reset(Kernel *pObjectPtr) {
		if (m_pObjectPtr != pObjectPtr)
		{
			delete m_pObjectPtr;
		}
		m_pObjectPtr = pObjectPtr; 
	}

	Kernel * KernelAutoPtr::operator->() const { 
		return m_pObjectPtr; 
	}

	Kernel & KernelAutoPtr::operator*() const { 
		return *m_pObjectPtr; 
	}

	HANDLE KernelAutoPtr::GetHandle(void) const {
		return m_pObjectPtr->GetHandle();
	}

	DWORD KernelAutoPtr::Status(void) const {
		return m_pObjectPtr->Status();
	}

	BOOL KernelAutoPtr::IsNull(void) const {
		return (m_pObjectPtr == NULL);
	}

}