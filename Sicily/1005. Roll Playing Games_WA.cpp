#include <iterator>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
using namespace std;
int DicesNum;
vector<int> FacesNumKnown;
vector<vector<int>> DicesKnown;
int TargetFacesNum, TargetSumsNum;
map<int, int> TargetWays;
map<int, int> WaysKnown;
vector<int> TargetDice;
vector<int> Possible;
map<int, int> PossibleMap;
int count0 = 0;

bool IsValid()
{
	map<int, int> WaysRslt;
	for (auto p : WaysKnown)
	{
		int Sum = p.first;
		for (auto i = 0; i < TargetFacesNum; ++i)
		{
			int S = Sum + TargetDice[i];
			if (WaysRslt.find(S) == WaysRslt.end())
				WaysRslt[S] = WaysKnown.at(Sum);
			else WaysRslt.at(S) = WaysRslt.at(S) + WaysKnown.at(Sum);
		}
	}
	for (auto i : TargetWays)
	{
		auto itr = WaysRslt.find(i.first);
		if (itr == WaysRslt.end() || itr->second != i.second)
		{
			/*for (auto i = 0; i < TargetFacesNum; ++i)
				cout << " " << TargetDice[i];
			cout << endl;*/
			return false;
		}

	}
	return true;
}

void BuildPossible()
{
	Possible.clear();
	PossibleMap.clear();
	vector<int> Impossible;

	for (auto i : TargetWays)
	{
		for (auto j : WaysKnown)
		{
			int t = i.first - j.first;
			int limit = i.second / j.second;
			if (t<=0)
				continue;
			if (i.second < j.second)
			{
				Impossible.push_back(t);
				continue;
			}
			auto itr = PossibleMap.find(t);
			if (itr != PossibleMap.end())
				itr->second = limit < itr->second ? limit : itr->second;
			else PossibleMap.insert({ t,limit });
		}
	}
	auto itr = PossibleMap.begin();
	while (itr != PossibleMap.end())
	{
		if (find(Impossible.begin(), Impossible.end(), itr->first) != Impossible.end())
		{
			itr=PossibleMap.erase(itr); continue;
		}
		++itr;
	}
	for (auto i : PossibleMap)
	{
		for (auto j = 0; j < i.second; ++j)
			Possible.push_back(i.first);
	}
}


void BuildSums()
{
	WaysKnown.clear();
	for (auto d = 0; d < DicesNum; ++d)
	{
		int FacesNum = FacesNumKnown[d];
		if (d == 0)
		{
			for (auto f = 0; f < FacesNum; ++f)
				WaysKnown.insert({ DicesKnown[d][f],1 });
			continue;
		}
		map<int, int> WaysRslt;
		for (auto p:WaysKnown)
		{
			int Sum = p.first;
			for (auto i = 0; i < FacesNum; ++i)
			{
				int S = Sum + DicesKnown[d][i];
				if (WaysRslt.find(S) == WaysRslt.end())
					WaysRslt[S] = WaysKnown.at(Sum);
				else WaysRslt.at(S) = WaysRslt.at(S) + WaysKnown.at(Sum);
			}
		}
		WaysKnown.clear(); WaysKnown = WaysRslt; WaysRslt.clear();
	}
}

bool DFS(int DicePos, int PossiblelPos)
{
	if (DicePos != -1)
		TargetDice[DicePos] = Possible[PossiblelPos];
	if (int(Possible.size()) - PossiblelPos < TargetFacesNum -DicePos)
		return false;
	if (DicePos == TargetFacesNum-1)
	{
		++count0;
		if (IsValid())
		{
			cout << "Final die face values are";
			for (auto i = 0; i < TargetFacesNum; ++i)
				cout << " " << TargetDice[i];
			cout << endl;
			return true;
		}
		else return false;
	}
	for (int i= PossiblelPos+1;i<int(Possible.size());++i)
	{
		if (DFS(DicePos + 1, i))
			return true;
	}
	return false;
}
int main()
{
	
	while (cin >> DicesNum)
	{
		if (DicesNum == 0)
			break;
		FacesNumKnown.resize(DicesNum);
		DicesKnown.resize(DicesNum);
		for (auto i = 0; i < DicesNum; ++i)
		{
			cin >> FacesNumKnown[i];
			DicesKnown[i].resize(FacesNumKnown[i]);
			for (auto j = 0; j < FacesNumKnown[i]; ++j)
				cin >> DicesKnown[i][j];
		}
		cin >> TargetFacesNum >> TargetSumsNum;
		TargetDice.clear();
		TargetDice.resize(TargetFacesNum);
		TargetWays.clear();
		int Sums,Ways;
		for (auto i = 0; i < TargetSumsNum; ++i)
		{
			cin >> Sums >> Ways;
			TargetWays.insert({ Sums,Ways });
		}
		


		cout << "TargetWays:" << endl;
		for (auto i : TargetWays)
			cout << "(" << i.first << "," << i.second << ") ";
		cout << endl;
		BuildSums();
		cout << "WaysKnown:" << endl;
		for (auto i : WaysKnown)
			cout << "(" << i.first << "," << i.second << ") ";
		cout << endl;
		BuildPossible();
		cout << "PossibleMap:" << endl;
		for (auto i : PossibleMap)
			cout << "(" << i.first << "," << i.second << ") ";
		cout << endl;
	
		/*if (!DFS(-1,-1))
			cout << "Impossible" << endl;*/
		//cout << count0 << endl;

	}
	
	return 0;
}
