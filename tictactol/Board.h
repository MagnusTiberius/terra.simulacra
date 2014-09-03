#pragma once

#include <ShlObj.h>
#include <algorithm>
#include <string>
#include <map>
#include "Util.h"
#include "User.h"
#include <utility>  

namespace bbg {

class Board
{
public:
	Board(void);
	~Board(void);
public:
	std::wstring GetId(void);
	void JoinBoard(User* v);
	void LeaveBoard(User* v);
private:
	std::wstring m_Id;
	std::map<std::string, User*> m_UserList;
};




}