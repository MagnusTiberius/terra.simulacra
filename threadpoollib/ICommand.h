#pragma once

namespace bbg {

using namespace bbg;

class ICommand
{
public:
	ICommand(void);
	~ICommand();
	virtual  void Execute(void) = 0;
};

}