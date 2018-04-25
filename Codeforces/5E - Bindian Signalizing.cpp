#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	int num;
	cin >> num;
	vector<int> input(num);
	for (auto i = 0; i < num; ++i)
		cin >> input[i];

	auto highest = max_element(input.begin(), input.end());
	auto high_pos = distance(highest, input.end());
	vector<int> hill(num + 2);
	hill.front() = numeric_limits<int>::max();
	copy(highest, input.end(), hill.begin() + 1);
	copy(input.begin(), highest, hill.begin() + 1 + high_pos);
	hill.back() = numeric_limits<int>::max();

	int *left = new int[num + 1], *right = new int[num + 1];
	vector<int> same(num + 1);
	for (auto i = 1; i <= num; ++i)
	{
		auto p = i - 1;
		while (hill[p] < hill[i])
			p = left[p];
		left[i] = hill[p] == hill[i] ? left[p] : p;
	}
	for(auto i=num;i>=1;--i)
	{
		auto p = i + 1;
		while (hill[p] < hill[i])
			p = right[p];
		same[i] = hill[p] == hill[i] ? same[p] + 1 : 0;
		right[i] = hill[p] == hill[i] ? right[p] : p;
	}

	long long rslt{ 0 };
	for (auto i = 1; i <= num; ++i)
	{
		if (left[i] >= 1)
			++rslt;
		if (right[i] <= num)
			++rslt;
		else if (left[i] > 1)
			++rslt;
		rslt += same[i];
	}
	cout << rslt << endl;
	return 0;
}