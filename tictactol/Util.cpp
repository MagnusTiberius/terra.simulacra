#include "Util.h"
#include <time.h> 
#include "stdio.h"
#include "stdlib.h"
#include <random>
#include <cstdlib>
#include <iostream>
#include <ctime>

namespace bbg {

Util::Util(void)
{
	srand (time(NULL));
}


Util::~Util(void)
{
}

string Util::GetRandomQuote()
{
	//https://www.cs.cmu.edu/~pattis/quotations.html
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
	quotes.push_back("All programmers are playwrights and all computers are lousy actors.");
	quotes.push_back("Bad code isn't bad, its just misunderstood.");
	quotes.push_back("Debugging is anticipated with distaste, performed with reluctance, and bragged about forever.");
	quotes.push_back("Experience is a poor teacher: it gives its tests before it teaches its lessons.");
	quotes.push_back("If I had eight hours to chop down a tree, I would spend 6 hours sharpening an axe.");
	quotes.push_back("If you understand what you're doing, you're not learning anything.");
	quotes.push_back("In theory, there is no difference between theory and practice, but not in practice.");
	quotes.push_back("It is easier to measure something than to understand what you have measured.");
	quotes.push_back("Measure twice, cut once.");
	quotes.push_back("Microsoft, where quality is job 1.1");
	quotes.push_back("Programs for sale: Fast, Reliable, Cheap: choose two.");
	quotes.push_back("Real programmers don't comment their code. If it was hard to write, it should be hard to understand.");
	quotes.push_back("Recurses! Called again.");
	quotes.push_back("The person who knows HOW will always have a job. The person who knows WHY will always be his/her boss.");
	quotes.push_back("The sooner you get behind in your work, the more time you have to catch up.");
	quotes.push_back("There are only 10 different kinds of people in the world: those who know binary and those who don't.");
	quotes.push_back("Think (design) globally; act (code) locally.");
	quotes.push_back("Think twice, code once.");
	quotes.push_back("Time is an excellent teacher, but eventually it kills all its students.");
	quotes.push_back("Weeks of programming can save you hours of planning.");
	quotes.push_back("When a programming language is created that allows programmers to program in simple English, it will be discovered that programmers cannot speak English.");
	quotes.push_back("Why do we never have time to do it right, but always have time to do it over?");
	quotes.push_back("By viewing the old we learn the new.");
	quotes.push_back("Give me a fish and I eat for a day. Teach me to fish and I eat for a lifetime.");
	quotes.push_back("He who asks is a fool for five minutes; he who does not ask remains a fool forever.");
	quotes.push_back("Teachers open the door, but you must enter by yourself.");
	quotes.push_back("Tell me and I forget. Show me and I remember. Involve me and I understand.");
	quotes.push_back("The first step towards wisdom is calling things by their right names.");
	int sz = quotes.size();
	int m = rand();
	int n = m % sz;
	printf("n=%d; m=%d\n",n,m);
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

std::vector<string> Util::GatherMessages(char* str, int len)
{
	std::vector<string> list;
	string message;
	BOOL isValid = false;
	for(int i=0; i<len; i++)
	{
		isValid = false;
		while(str[i]!=';' && i<len) 
		{
			message = message + str[i];
			i++;
		}
		if (str[i]==';') 
			isValid = true;
		if (i<len)
		{
			message = message + str[i];
			i++;
		}
		if (message.size() > 0 && isValid)
			list.push_back(message);
		message = "";
	}
	return list;
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
				if (i<len) i++;
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
				if (i<len) i++;
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
			while((str[i] !=' ' && str[i] !=';') && i<len) 
			{
				token = token + str[i];
				i++;
			}
			if (str[i] ==';' && i<len)
			{
				i++;
			}
			list.push_back(token);
		}
	}
	return list;
}

}