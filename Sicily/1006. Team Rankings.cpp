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
#include <string>
#include <sstream>
using namespace std;
//using RANK = array<char, 5>;
//using RELATIVE_PAIR = array<char, 2>;
//using RELATIVE_ORDER = vector<RELATIVE_PAIR>;

typedef array<char, 5> RANK;
typedef array<char, 2> RELATIVE_PAIR;
typedef vector<RELATIVE_PAIR> RELATIVE_ORDER;

int NumRanking;
vector<RANK> InputRankings;
vector<RANK> AllRankings;
vector<int> ValueMap;

RANK Pool;
RANK Permut;
array<int,5> PoolPosUsed;
int Count;


RELATIVE_ORDER GetRelatOrder(RANK &R)
{
	RELATIVE_ORDER RelateOrder;
	RELATIVE_PAIR rp;
	for (auto i = 0; i < 5; ++i)
	{
		for (auto j = i + 1; j < 5; ++j)
		{
			rp[0] = R[i]; rp[1] = R[j];
			RelateOrder.push_back(rp);
		}
	}
	return RelateOrder;
}

int GetValue(RANK &R1, RANK &R2)
{
	RELATIVE_ORDER RO1 = GetRelatOrder(R1);
	RELATIVE_ORDER RO2 = GetRelatOrder(R2);
	int n = 0; bool Found = false;
	for (auto x : RO1)
	{
		Found = false;
		for (auto y : RO2)
		{
			if (x[0] == y[0] && x[1] == y[1])
			{
				Found = true; break;
			}
		}
		if (Found)
			continue;
		else ++n;
	}
	return n;
}

bool Permutate(int PermutPos)
{
	if (PermutPos == int(Permut.size()))
	{
		++Count;
		AllRankings.push_back(Permut);
		return false;
	}
	//for Permut[PermutPos], try with Pool[i]
	//i is not used by Permut[0:PermutPos]
	for (int i = 0; i<int(Pool.size()); ++i)
	{
		if (find(PoolPosUsed.begin(), PoolPosUsed.begin() + PermutPos, i) != PoolPosUsed.begin() + PermutPos)
			continue;
		Permut[PermutPos] = Pool[i];
		PoolPosUsed[PermutPos] = i;
		if (Permutate(PermutPos + 1))
			return true;
	}
	return false;
}

void BuildAllRankings()
{
	Pool[0] = 'A'; Pool[1] = 'B'; Pool[2] = 'C'; Pool[3] = 'D'; Pool[4] = 'E';
	AllRankings.clear();
	Count = 0;
	Permutate(0);
}


void BuildValueMap()
{
	BuildAllRankings();
	int Siz = AllRankings.size();
	ValueMap.clear();
	ValueMap.resize(Siz);
	int value=0;
	for (auto i=0;i<Siz;++i)
	{
		value = 0;
		for (auto RI : InputRankings)
			value = value + GetValue(AllRankings[i], RI);
		ValueMap[i] = value;
	}
}

int main()
{
	while (cin >> NumRanking)
	{
		if (NumRanking == 0)
			break;
		InputRankings.resize(NumRanking);
		string str; getline(cin, str);
		for (auto i = 0; i < NumRanking; ++i)
		{
			getline(cin, str);
			for (auto j = 0; j < 5; ++j)
				InputRankings[i][j] = str[j];
		}
		BuildValueMap();
		int index, value=65535;
		for (auto i=0;i<int(ValueMap.size());++i)
		{
			if(ValueMap[i]<value)
			{
				index = i;
				value = ValueMap[i];
			}
		}
		for (auto i = 0; i < 5; ++i)
			cout << AllRankings[index][i];
		cout << " is the median ranking with value " << value <<"."  << endl;
	}
	return 0;
}