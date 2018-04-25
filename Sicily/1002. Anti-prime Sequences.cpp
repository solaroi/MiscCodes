#include <iterator>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
using namespace std;
int Low, Upper, Degree;
vector<int> IsPrime;
vector<int> AntiPrimeSeq;

void SetPrime()
{
	IsPrime.resize(Upper*Degree+2);
	for (auto &x : IsPrime)
		x = 1;
	for (auto Num = 3; Num <= Upper*Degree+1; ++Num)
	{
		for (auto D = 2; D < Num; ++D)
		{
			if (Num%D == 0)
			{
				IsPrime[Num] = 0; break;
			}
		}
	}
}

bool IsValid(int Pos)
{
	for (auto i = 0; i < Pos; ++i)
	{
		if (AntiPrimeSeq[i] == AntiPrimeSeq[Pos])
			return false;
	}
	int Sum = AntiPrimeSeq[Pos];
	for (auto i = Pos - 1; i >= 0 && i >= Pos - Degree + 1; --i)
	{
		Sum = Sum + AntiPrimeSeq[i];
		if (IsPrime[Sum] == 1)
			return false;
	}
	return true;
		
}

bool DFS(int Pos)
{
	if (Pos == Upper - Low + 1)
	{
		cout << AntiPrimeSeq[0];
		for (auto i = 1; i < Pos; ++i)
			cout << ","<< AntiPrimeSeq[i];
		cout << endl;
		return true;
	}
	for (auto Num = Low; Num <= Upper; ++Num)
	{
		AntiPrimeSeq[Pos] = Num;
		if (IsValid(Pos) && DFS(Pos + 1))
			return true;
	}
	return false;
}

int main()
{
	
	while (cin >> Low >> Upper >> Degree)
	{
		if (Low == 0 && Upper == 0 && Degree == 0)
			break;
		SetPrime();
		AntiPrimeSeq.resize(Upper - Low + 1);
		if (!DFS(0))
			cout << "No anti-prime sequence exists." << endl;
	}
	return 0;
}
