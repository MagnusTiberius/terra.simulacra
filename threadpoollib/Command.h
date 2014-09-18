#pragma once
#include "ICommand.h"

namespace bbg {

using namespace bbg;

class Command : public ICommand
{
public:
	Command();
	~Command();
	virtual  void Execute(void);
};

}