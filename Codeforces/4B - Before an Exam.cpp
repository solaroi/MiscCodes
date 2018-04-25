
#include <iostream>
using namespace std;

int main()
{
	int d, sum_time, *min_time, *max_time;
	cin >> d >> sum_time;
	min_time = new int[d];
	max_time = new int[d];
	int min_sum{ 0 }, max_sum{ 0 };
	for (auto i = 0; i < d; ++i)
	{
		cin >> min_time[i] >> max_time[i];
		min_sum += min_time[i];
		max_sum += max_time[i];
	}
	if (sum_time<min_sum || sum_time>max_sum)
	{
		cout << "NO" << endl;
		return 0;
	}
	int current_sum = min_sum, cnt{ 0 };
	while (current_sum < sum_time)
	{
		current_sum = current_sum + max_time[cnt] - min_time[cnt];
		min_time[cnt] = max_time[cnt];
		++cnt;
	}
	if (cnt != 0)
	{
		--cnt;
		min_time[cnt] = min_time[cnt] - (current_sum - sum_time);
	}
	cout << "YES" << endl;
	for (auto i = 0; i < d; ++i)
		cout << min_time[i] << " ";
	cout << endl;
	return 0;
}

