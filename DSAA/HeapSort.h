#pragma once
#include <vector>
using namespace std;
inline size_t left(size_t i) { return 2 * i; };
inline size_t right(size_t i) { return 2 * i + 1; };
inline size_t parent(size_t i) { return i / 2; };

struct Heap0 
{
	Heap0() { Vct.push_back(DBL_MAX); Siz = 1; };
	vector<double> Vct;
	size_t Siz;
};


void MaxHeapify(Heap0 &heap, size_t idx)
{
	size_t lrgst{ idx };
	if (right(idx) <= heap.Siz && heap.Vct[right(idx)] > heap.Vct[idx])
		lrgst = right(idx);
	if (left(idx) <= heap.Siz && heap.Vct[left(idx)] > heap.Vct[lrgst])
		lrgst = left(idx);
	if (lrgst != idx)
	{
		swap(heap.Vct[lrgst], heap.Vct[idx]);
		MaxHeapify(heap, lrgst);
	}
}

void BuildMaxHeap(Heap0 &heap, vector<double> &vct)
{
	//heap.Vct[0] = { DBL_MAX };
	for (auto i : vct)
		heap.Vct.push_back(i);
	heap.Siz = vct.size();
	for (size_t i = parent(heap.Siz); i >= 1; --i)
		MaxHeapify(heap, i);
}


void HeapSort(vector<double> &vct)
{
	Heap0 heap;
	BuildMaxHeap(heap, vct);
	//swap(heap.Vct[heap.Siz], heap.Vct[1]);
	while (heap.Siz != 1)
	{
		MaxHeapify(heap, 1);
		swap(heap.Vct[heap.Siz], heap.Vct[1]);
		--heap.Siz;
	}
	for (size_t i = 0; i < vct.size(); ++i)
		vct[i] = heap.Vct[i + 1];
}