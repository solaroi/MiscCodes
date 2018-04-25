#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	set<string> Type{ "int","bool","short","float","double","long"};
	multimap<string,int> IdentifierIndex;
	ifstream FileInput("F:/Visual Studio 2015/src.cpp");
	string StrLine;
	int LineIndex = 0;
	while (getline(FileInput, StrLine))
	{
		++LineIndex;
		if (StrLine[0] == '/' && StrLine[1] == '/')
			continue;
		if (StrLine[0] == '/' && StrLine[1] == '*')
		{
			while (!(StrLine.back() == '/' && StrLine[StrLine.size() - 2] == '*'))
			{
				getline(FileInput, StrLine); ++LineIndex;
			}
			continue;
		}

		stringstream SRead(StrLine);
		string Expression;
		while (SRead >> Expression)
		{
			if (Type.find(Expression) != Type.end())
			{
				bool IsParted = true;
				SRead >> Expression; 
				string RemainExpr = Expression;
				while (IsParted)
				{
					//cout << RemainExpr << " ";
					string FirstPart;
					auto Comma = find(RemainExpr.cbegin(), RemainExpr.cend(), ',');
					copy(RemainExpr.cbegin(), Comma, back_inserter(FirstPart));
					auto rlowerbound = find_if(FirstPart.crbegin(), FirstPart.crend(), [](char chr)\
					{return chr == '&' || chr == '*'; });
					auto upperbound = find_if(FirstPart.cbegin(), FirstPart.cend(), [](char chr)\
					{return chr == '=' || chr == '[' || chr == '{' || chr == '(' || chr == ';'; });
					/*cout << *rlowerbound.base() << " ";
					if (upperbound != FirstPart.end())
						cout << *upperbound;
					cout << endl;*/
					string Identifier;
					copy(rlowerbound.base(), upperbound, back_inserter(Identifier));
					IdentifierIndex.insert({ Identifier,LineIndex });
					if (Comma == RemainExpr.cend() || Comma == --RemainExpr.cend())
						IsParted = false;
					else
					{
						string Temp;
						copy(++Comma, RemainExpr.cend(), back_inserter(Temp));
						RemainExpr = Temp;
					}
				}
			}

		}
	}
	
	for (auto Pair : IdentifierIndex)
		cout << "Line "<<Pair.second << ": " << Pair.first << endl;
	return 0;
}


//F: / Visual Studio 2015 / src.cpp
//Hellow World!
//int i1 = 0;
////int i9=10;
//int i2, i3 = 0;
//int p1[10];
// /*double d9=20
// long d9=30*/
// double d1(9), d2{ 2 };
// long l1 = 100;