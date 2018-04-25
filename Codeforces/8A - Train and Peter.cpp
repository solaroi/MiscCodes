#include <iostream>
#include <string>
using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	string flags, seq1, seq2;
	cin >> flags >> seq1 >> seq2;

	int len_flags = flags.size(), len1 = seq1.size(), len2 = seq2.size();
	int dir[2]; dir[0] = 0; dir[1] = 0;
	for (int i = 0; i <= len_flags - len1; ++i)
	{
		if (flags.substr(i, len1) == seq1)
		{
			for (int j = i + len1; j <= len_flags - len2; ++j)
			{
				if (flags.substr(j, len2) == seq2)
				{
					dir[0] = 1; break;
				}
			}
			break;
		}
	}

	string rseq1, rseq2;
	for (int i = 0; i < len1; ++i)
		rseq1.push_back(seq1[len1 - 1 - i]);
	for (int i = 0; i < len2; ++i)
		rseq2.push_back(seq2[len2 - 1 - i]);
	for (int i = 0; i <= len_flags - len2; ++i)
	{
		if (flags.substr(i, len2) == rseq2)
		{
			for (int j = i + len2; j <= len_flags - len1; ++j)
			{
				if (flags.substr(j, len1) == rseq1)
				{
					dir[1] = 1; break;
				}
			}
			break;
		}
	}
	int x = dir[0] * 10 + dir[1];
	switch (x) 
	{
	case 00: {cout << "fantasy" << endl; break; }
	case 01: {cout << "backward" << endl; break; }
	case 10: {cout << "forward" << endl; break; }
	case 11: {cout << "both" << endl; break; }
	}
	return 0;
}
