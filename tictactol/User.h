#pragma once

#include <string>
#include "Util.h"

namespace bbg {

class User
{
public:
	User(void);
	~User(void);
public:
	void SetLoginId(std::string v);
	std::string GetLoginId(void);
private:
	std::string m_LoginId;
};


}