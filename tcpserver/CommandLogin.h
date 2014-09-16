#pragma once
#include "Command.h"

namespace bbg {

using namespace bbg;

class CommandLogin : public Command
{
public:
	CommandLogin();
	~CommandLogin();
	virtual  void Execute(void);
};

}