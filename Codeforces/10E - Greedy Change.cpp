//Apolynomial-time algorithm for the change-making problem
//Theorem 1. M(w) agrees with G(ci−1−1) in entries 1 through j − 1, and is one greater in entry j . 
//The remaining entries mj+1, . . . , mn are all zero.
//G(x) is the greedy representation of x
//The minimal representation of x, denoted by M(x), is the lexicographically greatest of all the representations of x of minimum size.
#include<iostream>
using namespace std;

const int int_max = 2000000000;
int num_coins;
int *coins;

int inner_product(int *v1, int *v2)
{
	int product{ 0 };
	for (int i = 0; i < num_coins; ++i)
		product += v1[i] * v2[i];
	return product;
}


int* greedy(int val)
{
	int *represent = new int[num_coins];
	for (int j = 0; j < num_coins; ++j)
	{
		represent[j] = val / coins[j];
		val %= coins[j];
	}
	return represent;
}



int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> num_coins;
	coins = new int[num_coins];
	int *all_one = new int[num_coins];
	for (int i = 0; i < num_coins; ++i)
	{
		cin >> coins[i];
		all_one[i] = 1;
	}
		
	int minx{ int_max };
	for (int i = 1; i < num_coins; ++i)
	{
		int *greedy_i_1 = greedy(coins[i - 1] - 1);
		int *minimal = new int[num_coins];
		for (int j = 1; j < num_coins; ++j)
		{
			for (int k = 0; k <= j - 1; ++k)
				minimal[k] = greedy_i_1[k];
			minimal[j] = greedy_i_1[j] + 1;
			for (int k = j + 1; k < num_coins; ++k)
				minimal[k] = 0;
			int w = inner_product(minimal, coins);
			int *greedy_w = greedy(w);
			int norm_greedy = inner_product(greedy_w, all_one);
			int norm_minimal = inner_product(minimal, all_one);
			if (norm_minimal < norm_greedy && w < minx)
				minx = w;
			delete greedy_w;
		}
		delete minimal, greedy_i_1;
	}
	
	if (minx == int_max)
		minx = -1;
	cout << minx << endl;
	delete all_one, coins;
	return 0;
}


