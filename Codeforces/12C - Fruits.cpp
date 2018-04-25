#include<iostream>
#include<string>
using namespace std;
int fruit_kinds, buy_amount;
int *prices, *fruit_amount;
string *fruit;
int len_fruit{ 0 };

void swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void InsertSort(int *arr, int left, int right)
{
	if (right - left + 1 <= 1)
		return;
	for (int i = left; i <= right; ++i)
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


void QuickSort(int *arr, int left, int right)
{
	if (right - left + 1 <= 10)
	{
		InsertSort(arr, left, right);
		return;
	}
	int center = (left + right) / 2;
	//to reduce the chance of worst cases
	if (arr[left] > arr[right])
		swap(arr, left, right);
	if (arr[left] > arr[center])
		swap(arr, left, center);
	if (arr[center] > arr[right])
		swap(arr, center, right);
	int p = arr[center];
	swap(arr, center, right);
	int i = left, j = right - 1;
	while (true)
	{
		while (arr[i] < p)
			++i;
		while (arr[j] > p)
			--j;
		if (i > j)
			break;
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		++i; --j;
	}
	swap(arr, i, right);
	QuickSort(arr, left, i - 1);
	QuickSort(arr, i + 1, right);
}

int FindFruit(string str)
{
	for (int i = 0; i < len_fruit; ++i)
		if (fruit[i] == str)
			return i;
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> fruit_kinds >> buy_amount;
	prices = new int[fruit_kinds];
	fruit = new string[fruit_kinds];
	fruit_amount = new int[fruit_kinds];
	for (int i = 0; i < fruit_kinds; ++i)
		cin >> prices[i];
	
	for (int i = 0; i < buy_amount; ++i)
	{
		string instr;
		cin >> instr;
		int x = FindFruit(instr);
		if (x >= 0)
			++fruit_amount[x];
		else
		{
			fruit[len_fruit] = instr;
			fruit_amount[len_fruit] = 1;
			++len_fruit;
		}
	}
	QuickSort(prices, 0, fruit_kinds - 1);
	QuickSort(fruit_amount, 0, len_fruit - 1);
	int min_cost{ 0 }, max_cost{ 0 };
	for (int i = 0; i < len_fruit; ++i)
	{
		min_cost += fruit_amount[i] * prices[len_fruit - 1 - i];
		max_cost += fruit_amount[i] * prices[fruit_kinds - len_fruit + i];
	}
	cout << min_cost << ' ' << max_cost << endl;
	return 0;
}


