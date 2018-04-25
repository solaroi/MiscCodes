#include<iostream>
using namespace std;
int digits[10];

void InsertSort(int *arr, int len)
{
	if (len <= 1)
		return;
	for (int i = 1; i < len; ++i)
	{
		int temp = arr[i];
		int j = i - 1;
		for (; j >= 0; --j)
		{
			if (arr[j] > temp)
				arr[j + 1] = arr[j];
			else break;
		}
		arr[j + 1] = temp;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int len = 0;
	char inbuf;
	while (true)
	{
		cin.get(inbuf);
		if (inbuf == '\n')
			break;
		digits[len] = inbuf - '0';
		++len;
	}
	InsertSort(digits, len);
	if (digits[0] == 0)
	{
		for (int i = 0; i < len; ++i)
		{
			if (digits[i] > 0)
			{
				digits[0] = digits[i];
				digits[i] = 0;
				break;
			}
		}
	}
	
	for (int i = 0; i<len; ++i)
	{
		if (digits[i] != cin.get() - '0')
		{
			cout << "WRONG_ANSWER" << endl;
			return 0;
		}
	}
	//in case Bob's answer is longer than correct answer
	if (cin.get() != '\n')
	{
		cout << "WRONG_ANSWER" << endl;
		return 0;
	}
	cout << "OK" << endl;
	return 0;
}


