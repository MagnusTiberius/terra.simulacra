#pragma once

#include <thread>
#include "Global.h"

namespace bbg{

	class WaitableObject
	{
	public:
		WaitableObject();
		~WaitableObject();
		virtual HANDLE GetHandle(void) const = 0;
		virtual DWORD Status(void) const = 0;
	};

}