#include<iostream>
#include<algorithm>
using namespace std;

//len_lcis[i][j] is the length of LCIS of seq1[1:i] and seq2[1:j]
//endpos1[i][j] is position of the last element of LCIS of seq1[1:i] and seq2[1:j]
//endpos2[i][j] is position of the second last element of LCIS of seq1[1:i] and seq2[1:j]
//endpos[i][j] / 501 is the position in seq1, endpos[i][j] % 501 is the position in seq2
//thus, endpos[i][j] = pos1*501 + pos2, pos1 <= 500, pos2 <= 500
int len1, len2, *seq1, *seq2;
int **len_lcis, **endpos1, **endpos2;

void init()
{
	len_lcis = new int*[len1 + 1];
	endpos1 = new int*[len1 + 1];
	endpos2 = new int*[len1 + 1];
	for (int i = 0; i <= len1; ++i)
	{
		len_lcis[i] = new int[len2 + 1];
		endpos1[i] = new int[len2 + 1];
		endpos2[i] = new int[len2 + 1];
		len_lcis[i][0] = 0;
		endpos1[i][0] = 0;
		endpos2[i][0] = 0;
	}
	for (int j = 0; j <= len2; ++j)
	{
		len_lcis[0][j] = 0;
		endpos1[0][j] = 0;
		endpos2[0][j] = 0;
	}
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	
	cin >> len1;
	seq1 = new int[len1 + 1];
	for (int i = 1; i <= len1; ++i)
		cin >> seq1[i];
	cin >> len2;
	seq2 = new int[len2 + 1];
	for (int i = 1; i <= len2; ++i)
		cin >> seq2[i];
	seq1[0] = -1; seq2[0] = -1;
	init();
	for (int i = 1; i <= len1; ++i)
	{
		for (int j = 1; j <= len2; ++j)
		{
			if (seq1[i] == seq2[j])
			{
				len_lcis[i][j] = len_lcis[i - 1][j - 1];
				if (seq1[i] > seq1[endpos1[i - 1][j - 1] / 501])
				{
					++len_lcis[i][j];
					endpos1[i][j] = i * 501 + j;
					endpos2[i][j] = endpos1[i - 1][j - 1];
				}
				else if (seq1[i] < seq1[endpos1[i - 1][j - 1] / 501] && seq1[i] > seq1[endpos2[i - 1][j - 1] / 501])
				{
					endpos1[i][j] = i * 501 + j;
					endpos2[i][j] = endpos2[i - 1][j - 1];
				}
				else
				{
					endpos1[i][j] = endpos1[i - 1][j - 1];
					endpos2[i][j] = endpos2[i - 1][j - 1];
				}
			}
			else
			{
				int l1 = len_lcis[i - 1][j], l2 = len_lcis[i][j - 1];
				if (l1 == l2)
				{
					int end1 = seq1[endpos1[i - 1][j] / 501], end2 = seq1[endpos1[i][j - 1] / 501];
					endpos1[i][j] = end1 <= end2 ? endpos1[i - 1][j] : endpos1[i][j - 1];
					endpos2[i][j] = end1 <= end2 ? endpos2[i - 1][j] : endpos2[i][j - 1];
					len_lcis[i][j] = l1;
				}
				else
				{
					endpos1[i][j] = l1 >= l2 ? endpos1[i - 1][j] : endpos1[i][j - 1];
					endpos2[i][j] = l1 >= l2 ? endpos2[i - 1][j] : endpos2[i][j - 1];
					len_lcis[i][j] = l1 >= l2 ? l1 : l2;
				}
			}
		}
	}
	
	int i = len1, j = len2, k = len_lcis[len1][len2];
	int *output = new int[len_lcis[len1][len2]];
	while (i*j != 0)
	{
		output[--k] = seq1[endpos1[i][j] / 501];
		int x = endpos2[i][j];
		i = x / 501;
		j = x % 501;
	}
	cout << len_lcis[len1][len2] << endl;
	for (int i = 0; i < len_lcis[len1][len2]; ++i)
		cout << output[i] << ' ';
	cout << endl;
	return 0;
}


