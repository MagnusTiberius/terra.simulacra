#pragma once

#include "ThreadHandler.h"

namespace bbg {

using namespace bbg;

class TaskThreadHandler : public ThreadHandler
{
public:
	TaskThreadHandler(void);
	~TaskThreadHandler(void);
	virtual unsigned ThreadHandlerProc(void);
};

}