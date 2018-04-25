#include <iostream>
#include <fstream> 
#include <sstream> 
#include <array>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <ctime>
using namespace std;
vector<double> LuckyList;
map<double,int> CounterM;
int NumCases, N, M;
int Counter;
void DFS(int LLPos)
{
	if (LLPos > N)
	{
		++Counter;
		/*for (auto i = 1; i <= N; ++i)
			cout << LuckyList[i] << " ";
		cout << endl;*/
		return;
	}
	for (int Num = int(2 * LuckyList[LLPos - 1]); Num <= int(M / pow(2, N - LLPos)); ++Num)
	{
		LuckyList[LLPos] = Num;
		DFS(LLPos + 1);
	}	
}

int main()
{
	/*cin >> NumCases;
	for (auto i = 1; i <= NumCases; ++i)
	{
		cin >> N >> M;
		LuckyList.clear(); LuckyList.resize(N + 1); LuckyList[0] = 0.5;
		Counter = 0;
		DFS(1);
		cout << "Case " << i << ": n = " << N << ", m = " << M << ", # lists = " << Counter << endl;
	}*/

	//Solution 2
	cin >> NumCases;
	for (auto i = 1; i <= NumCases; ++i)
	{
		cin >> N >> M;
		Counter = 0;
		CounterM.clear();
		CounterM.insert({ 0.5,1 });
		for (auto i = 1; i <= N; ++i)
		{
			map<double, int> temp;
			while (CounterM.size() != 0)
			{
				auto x = (*CounterM.begin()).first; auto counterx = (*CounterM.begin()).second;
				CounterM.erase(CounterM.begin());
				for (int y = 2 * x; y <= M / pow(2, N - i); ++y)
				{
					pair<double, int> yp{ y,1 };
					auto itr = temp.find(y);
					if (itr != temp.end())
						(*itr).second = (*itr).second + counterx;
					else temp[y] = counterx;
				}
			}
			CounterM.clear(); CounterM = temp;
			for (auto x : CounterM)
				cout << x.first << "-"<<x.second << "   ";
			cout << endl;
		}
		for (auto x : CounterM)
			Counter = Counter + x.second;
		cout << "Case " << i << ": n = " << N << ", m = " << M << ", # lists = " << Counter << endl;
	}

	return 0;
}

