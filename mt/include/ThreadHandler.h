#pragma once
#include "Global.h"

namespace bbg{

	class ThreadHandler
	{
	public:
		ThreadHandler();
		~ThreadHandler();
		virtual unsigned ThreadHandlerProc(void) = 0;
	};

}