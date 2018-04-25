#include <iostream>
using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	int num;
	cin >> num;
	int *chocolate = new int[num];
	for (auto i = 0; i < num; ++i)
		cin >> chocolate[i];
	if (num <= 2)
	{
		cout << 1 << ' ' << num - 1 << endl; return 0;
	}
	auto i = 0, j = num - 1;
	auto alice_left = chocolate[i], bob_left = chocolate[j];
	bool alice_prior{ false };
	while (j - i > 2)
	{
		if (alice_left < bob_left)
		{
			bob_left -= alice_left;
			++i;
			alice_left = chocolate[i];
		}
		else if (alice_left > bob_left)
		{
			alice_left -= bob_left;
			--j;
			bob_left = chocolate[j];
		}
		else
		{
			++i; --j;
			bob_left = chocolate[j];
			alice_left = chocolate[i];
		}
	}
	if (j - i == 2)
	{
		if (bob_left < alice_left)
			--j;
		else ++i;
	}
	cout << i + 1 << " " << num - j << endl;
	return 0;
}