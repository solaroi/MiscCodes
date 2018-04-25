#include <iostream>
#include <list>
using namespace std;

//mov M stepa from itr in circle
list<int>::iterator Mov(list<int> &L, list<int>::iterator itr, size_t M)
{
	size_t i = 0, j = 0;
	while (i < M%L.size())
	{
		++itr; ++i;
		if (itr == L.end())
			itr = L.begin();
	}
	return itr;
}

int main()
{
	size_t M = 10, N = 100;
	list<int> L;
	for (size_t i = 0; i <= N; ++i)
		L.push_back(i);
	auto itr = L.begin(), prv = itr;
	while (L.size() != 0)
	{
		itr = Mov(L, itr, M);
		cout << *itr << endl;
		itr = L.erase(itr);//itr points to the next node
		if (itr == L.end())
			itr = L.begin();
	}
	return 0;
}
