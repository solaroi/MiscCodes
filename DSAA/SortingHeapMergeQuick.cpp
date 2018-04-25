#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

void HeapSort(vector<double> &V)
{
	if (V.size() != 0)
	{
		priority_queue<double, vector<double>> Heap(V.begin(), V.end());
		for (auto &data : V)
		{
			data = Heap.top();
			if(Heap.size()!=0)
				Heap.pop();
		}
		reverse(V.begin(), V.end());
	}
	
}

//merge V[left]~V[centor] and V[centor+1]~V[right], result stored in Temp
//finally copy them back to V
void Merge(vector<double> &V, vector<double> &Temp, int left, int centorplus1, int right)
{
	auto ItrLeft = V.begin() + left;
	auto ItrCentorplus1 = V.begin() + centorplus1;
	auto ItrRight = V.begin() + right;
	auto ItrUpper = Temp.begin() + right - left + 1;
	merge(ItrLeft, ItrCentorplus1, ItrCentorplus1, ++ItrRight, Temp.begin());
	copy(Temp.begin(), ItrUpper, ItrLeft);
}

//sort V[left]~V[centor] and V[centor+1]~V[right]
//merge and restore back to V
void MergeSort(vector<double> &V, vector<double> &Temp, int left, int right)
{
	if (left < right)//for only one element, do nothing
	{
		int centor = (left + right) / 2;//cnetor is always less than right for at least 1 position
		MergeSort(V, Temp, left, centor);
		MergeSort(V, Temp, centor + 1, right);
		Merge(V, Temp, left, centor + 1, right);
	}
}

void MergeSort(vector<double> &V)
{
	if (V.size() != 0)
	{
		vector<double> Temp(V.size());//in the whole recursion process, only Temp is needed as new memory
		MergeSort(V, Temp, 0, V.size() - 1);
	}
}
int MakeMedian(vector<double> &V, int left, int right)
{
	int centor = (left + right) / 2;
	if (V[centor] < V[left])
		swap(V[centor], V[left]);
	if (V[right] < V[left])
		swap(V[right], V[left]);
	if (V[right] < V[centor])
		swap(V[centor], V[right]);
	swap(V[centor], V[right]);
	return V[right];
}
void QuickSort(vector<double> &V,int left,int right)
{
	//actually, it is better to use insertion sort when V.size()<=10
	if (left >= right)
		return;
	else if (right == left + 1)
	{
		if (V[right] < V[left])
			swap(V[right], V[left]);
	}
	else//patition could be implemented using std::partition in alogrithm
	{
		auto Pivot = MakeMedian(V, left, right);//get the pivot and rearrange for partition
		int i = 0, j = right ;
		while (true)
		{
			while (V[++i] < Pivot) {}
			while (V[--j] > Pivot) {}
			if (i < j)
				swap(V[i], V[j]);
			else
				break;
		}
		swap(V[i], V[right]);
		QuickSort(V, left, i - 1);
		QuickSort(V, i + 1, right);
	}
}

void QuickSort(vector<double> &V)
{
	QuickSort(V, 0, V.size()-1);
}

int main()
{
	vector<double> V{ 3,2,5,4,7,6,9,8,0,1};
	QuickSort(V);
	for (auto data : V)
		cout << data << " ";

	return 0;
}