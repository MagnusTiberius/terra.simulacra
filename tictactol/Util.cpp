#include "Util.h"
#include <time.h> 

namespace bbg {

Util::Util(void)
{
}


Util::~Util(void)
{
}

string Util::GetRandomQuote()
{
	std::vector<string> quotes;
	quotes.push_back("The question of whether a computer can think is no more interesting than the question of whether a submarine can swim.");
	quotes.push_back("C is quirky, flawed, and an enormous success.");
	quotes.push_back("An algorithm must be seen to be believed.");
	quotes.push_back("I don't know how many of you have ever met Dijkstra, but you probably know that arrogance in computer science is measured in nano-Dijkstras.");
	quotes.push_back("Suppose whatever we can recognize we can find. We can if P=NP.");
	quotes.push_back("The most important property of a program is whether it accomplishes the intention of its user.");
	quotes.push_back("Is it possible that software is not like anything else, that it is meant to be discarded: that the whole point is to always see it as a soap bubble?");
	quotes.push_back("Programs must be written for people to read, and only incidentally for machines to execute.");
	quotes.push_back("Good teaching is more a giving of the right questions than a giving of the right answers.");
	quotes.push_back("Computer Science is a science of abstraction -creating the right model for a problem and devising the appropriate mechanizable techniques to solve it.");
	quotes.push_back("Eighty percent of success is showing up.");
	quotes.push_back("Don't worry about people stealing your ideas. If your ideas are any good, you'll have to ram them down people's throats.");
	quotes.push_back("More is different.");
	quotes.push_back("Today, most software exists, not to solve a problem, but to interface with other software.");
	int sz = quotes.size();
	int m = rand();
	int n = m % sz;
	return quotes[n];
}

void Util::GenerateRandomChars(char *s, const int len) 
{
	srand (time(NULL));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
		int n = (sizeof(alphanum) - 1);
		int m = rand();
		int t = m % n;
        s[i] = alphanum[t];
    }
    s[len] = 0;
}


std::wstring Util::CreateGuid()
{
	::GUID guid;
	(void)::CoCreateGuid(&guid);
	//::UuidCreate(&guid);
	//sizeof char array provides count of chars (+2 for braces)(+1 for null)
	wchar_t buff[cchGUID + 2 + 1];
	//sizeof(x)/sizeof(*x) yields count of elements (cch)
	//the return value includes the null terminator
	auto ret = ::StringFromGUID2(guid, buff, sizeof(buff)/sizeof(*buff));
	//create string without {} -- minus 3 for null and {}
	std::wstring retval;
	if (ret > 3)
	{
		retval.reserve(cchGUID+1);
		retval.assign(&buff[1], ret-3);
	}
	transform( retval.begin(), retval.end(), retval.begin(), towlower);
	return retval;
}

std::vector<string> Util::Split(char* str,const char* delim)
{
    char* saveptr;
    char* token = strtok_s(str,delim, &saveptr);
    vector<string> result;
    while(token != NULL)
    {
        result.push_back(token);
        token = strtok_s(NULL,delim, &saveptr);
    }
    return result;
}

string Util::Token(int len)
{
	string t="";
	for(int i=0;i<len;i++)
	{
		switch(rand()%3)
		{
			case 0:
				t+=('0'+rand()%10);
				break;
			case 1:
				t+=('A'+rand()%26);
				break;
			case 2:
				t+=('a'+rand()%26);
				break;
		}
	}
	return t;
}

std::vector<string> Util::Parse(char* str,const char* delim, int len)
{
	std::vector<string> list;
	string token;
	for(int i=0; i<len; i++ )
	{
		while(str[i]==' ' && i<len) 
		{
			i++;
		}
		token = "";
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (str[i] == '\"' )
			{
				token = "";
				i++;
				while(str[i] !='\"' && i<len) 
				{
					token = token + str[i];
					i++;
				}
				i++;
				list.push_back(token);
			}
			if (str[i] == '\'' )
			{
				token = "";
				i++;
				while(str[i] !='\'' && i<len) 
				{
					token = token + str[i];
					i++;
				}
				i++;
				list.push_back(token);
			}
			if (str[i] != ' ' )
			{
				token = "";
				while(str[i] !=' ' && i<len) 
				{
					token = token + str[i];
					i++;
				}
			}
		}
		else
		{
			token = "";
			while(str[i] !=' ' && i<len) 
			{
				token = token + str[i];
				i++;
			}
			list.push_back(token);
		}
	}
	return list;
}

}