#include<iostream>
#include<set>
#include<utility>
using namespace std;
int num_houses;
double len_to_build;
set<pair<int, int>> houses;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> num_houses >> len_to_build;
	int center, len;
	for (int i = 0; i < num_houses; ++i)
	{
		cin >> center >> len;
		houses.insert({ center,len });
	}
	int rslt{ 2 };
	auto cur = houses.begin(), next = houses.begin();
	++next;
	while (next != houses.end())
	{
		double interval = (*next).first - (*cur).first - double((*next).second) / 2 - double((*cur).second) / 2;
		if (interval > len_to_build)
			rslt += 2;
		else if (interval == len_to_build)
			++rslt;
		++cur; ++next;
	}
	cout << rslt << endl;
	return 0;
}
