#pragma once

#include "Global.h"
#include "Kernel.h"
#include "Thread.h"
#include "Mutex.h"
#include "Semaphore.h"
#include "Event.h"

namespace bbg{

	class KernelAutoPtr
	{
	public:
		//KernelAutoPtr(void);
		virtual ~KernelAutoPtr(void) = 0;
		KernelAutoPtr(Kernel *pObjectPtr = NULL);
		Kernel * operator->() const;
		Kernel & operator*() const;
		HANDLE GetHandle(void) const;
		DWORD Status(void) const;
		BOOL IsNull(void) const;
	protected:
		void Reset(Kernel *pObjectPtr);
		Kernel *m_pObjectPtr;
	private:
		KernelAutoPtr(KernelAutoPtr & rhs);
		KernelAutoPtr & operator= (KernelAutoPtr & rhs);
	};




	template <class T>
	class DerivedAutoPtr : public KernelAutoPtr {
	public:
		DerivedAutoPtr(T *pObjectPtr = NULL) : KernelAutoPtr(pObjectPtr) {
		};

		DerivedAutoPtr<T> & operator= (T *pObjectPtr) {
			Reset(pObjectPtr);
			return *this; 
		};

		T * operator->() const {
			return static_cast<T *>(m_pObjectPtr); 
		};

		T & operator*() const {
			return *(static_cast<T *>(m_pObjectPtr));

		};
	};

	// typedef's for the autopointers we need in the library...
	typedef DerivedAutoPtr<Thread> ThreadAutoPtr;
	typedef DerivedAutoPtr<Mutex> MutexAutoPtr;
	typedef DerivedAutoPtr<Semaphore> SemaphoreAutoPtr;
	typedef DerivedAutoPtr<Event> EventAutoPtr;

}