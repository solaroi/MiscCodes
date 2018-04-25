
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
	map<string, set<array<int,2>>> name2score;
	int round_num;
	cin >> round_num;
	for (auto i = 1; i <= round_num; ++i)
	{
		string name; int score;
		cin >> name >> score;
		int new_score;
		if (name2score.find(name) != name2score.end())
			new_score = score + (*(--name2score[name].end())).back();
		else new_score = score;	
		name2score[name].insert({ i,new_score });
	}
	int last_largest_score = INT_MIN;
	for (auto ns : name2score)
	{
		if (last_largest_score < (*--ns.second.end()).back())
			last_largest_score = (*--ns.second.end()).back();
	}
	vector<string> candidates;
	for (auto ns : name2score)
	{
		if ((*--ns.second.end()).back() == last_largest_score)
			candidates.push_back(ns.first);
	}
	if (candidates.size() == 1)
	{
		cout << candidates.front() << endl;
		return 0;
	}
	int least_round = INT_MAX;
	string best_candidates;
	for (auto cand : candidates)
	{
		int first_overflow;
		for (auto records : name2score[cand])
		{
			if (records.back() >= last_largest_score)
			{
				first_overflow = records.front();	break;
			}
		}
		if (first_overflow < least_round)
		{
			least_round = first_overflow;
			best_candidates = cand;
		}
	}
	cout << best_candidates << endl;
	return 0;
}

