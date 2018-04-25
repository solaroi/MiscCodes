#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <cmath>
using namespace std;

bool Validate(string Str)
{
	string Vct;
	for (auto chr : Str)
	{
		if (chr == '(' || chr == '[' || chr == '{')
			Vct.push_back(chr);
		else if (chr == ')')
		{
			if (!Vct.empty() && Vct.back() == '(')
				Vct.pop_back();
			else return 0;
		}
		else if (chr == ']')
		{
			if (!Vct.empty() && Vct.back() == '[')
				Vct.pop_back();
			else return 0;
		}
		else if (chr == '}')
		{
			if (!Vct.empty() && Vct.back() == '[')
				Vct.pop_back();
			else return 0;
		}
	}
	if (!Vct.empty())
		return 0;
	return 1;
}

//priority: + - * / ^
double prrt(char chr)
{
	if (chr == '+')
		return 0;
	else if (chr == '-')
		return 0.1;
	else if (chr == '*')
		return 1;
	else if (chr == '/')
		return 1.1;
	else if (chr == '^')
		return 1.2;
	else if (chr == '(' || chr == ')' || chr == '[' || chr == ']'\
		|| chr == '{' || chr == '}')
		return -1;
	else return 0;
}
string In2Post(string Str)
{
	string Oprtor, Rslt;
	string rslt;
	for (auto itr = Str.begin(); itr != Str.end(); ++itr)
	{
		if (*itr == ')')
		{
			while (Oprtor.back() != '(')
			{
				Rslt.push_back(Oprtor.back());
				Oprtor.pop_back();
			}
			Oprtor.pop_back();//pop '(' 
		}
		else if (*itr == ']')
		{
			while (Oprtor.back() != '[')
			{
				Rslt.push_back(Oprtor.back());
				Oprtor.pop_back();
			}
			Oprtor.pop_back();//pop '[' 
		}
		else if (*itr == '}')
		{
			while (Oprtor.back() != '{')
			{
				Rslt.push_back(Oprtor.back());
				Oprtor.pop_back();
			}
			Oprtor.pop_back();//pop '{' 
		}
		//when low-prio operator encounterd, cal the higher-prio expression in front right away
		else if (*itr == '+' || *itr == '-' || *itr == '*' || *itr == '/')
		{
			while (!Oprtor.empty() && prrt(Oprtor.back()) > prrt(*itr))
			{
				Rslt.push_back(Oprtor.back());
				Oprtor.pop_back();
			}
			Oprtor.push_back(*itr);
		}
		else if (*itr == '(' || *itr == '^' || *itr == '[' || *itr == '{')
			Oprtor.push_back(*itr);
		else Rslt.push_back(*itr);
	}
	while (!Oprtor.empty())
	{
		Rslt.push_back(Oprtor.back());
		Oprtor.pop_back();
	}
	return Rslt;
}

string Post2In(const string Str)
{
	vector<string> Vstr;
	string prv;
	for (size_t i=0; i<Str.size(); ++i)
	{
		if (Str[i] == '+' || Str[i] == '-' || Str[i] == '*' || Str[i] == '/' || Str[i] == '^')
		{
			prv = Vstr.back();
			Vstr.pop_back();
			Vstr.back() = "(" + Vstr.back() + Str.substr(i,1) + prv + ")";
		}
		else Vstr.push_back(Str.substr(i, 1));
	}
	return *Vstr.begin();
}

double CalPost(string str)
{
	vector<double> Vdb;
	for (auto chr : str)
	{
		double prv;
		if (chr == '/')
		{
			prv = Vdb.back();
			Vdb.pop_back();
			Vdb.back() = Vdb.back() / prv;
		}
		else if (chr == '*')
		{
			prv = Vdb.back();
			Vdb.pop_back();
			Vdb.back() = Vdb.back() * prv;
		}
		else if (chr == '+')
		{
			prv = Vdb.back();
			Vdb.pop_back();
			Vdb.back() = Vdb.back() + prv;
		}
		else if (chr == '-')
		{
			prv = Vdb.back();
			Vdb.pop_back();
			Vdb.back() = Vdb.back() - prv;
		}
		else if (chr == '^')
		{
			prv = Vdb.back();
			Vdb.pop_back();
			Vdb.back() = pow(Vdb.back(), prv);
		}
		else
			Vdb.push_back(double(chr - '0'));
	}
	return *Vdb.begin();
}