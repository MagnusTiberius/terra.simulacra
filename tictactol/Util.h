#pragma once

#include <random>
#include <string>
#include <ShlObj.h>
#include <algorithm>

using namespace std;

namespace bbg {

const size_t cchGUID = sizeof("8278a894-5875-4907-b3ed-fb3ac5f6ff6c")-1;
//const wchar_t *zero_guid = L"00000000-0000-0000-0000-000000000000";

class Util
{
public:
	Util(void);
	~Util(void);
	static void Util::GenerateRandomChars(char *s, const int len) ;
	static std::wstring CreateGuid();
	static std::vector<string> Split(char* str,const char* delim);
	static string Token(int len);
	static std::vector<string> Parse(char* str,const char* delim, int len);
	static string Util::GetRandomQuote();
	static std::vector<string> GatherMessages(char* buf, int len);
};


}