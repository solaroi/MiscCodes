#include <iostream>
using namespace std;
//Page 117 3.11
//this single list is designed to be a set
//
template <typename Object>
struct Node
{
	Node() :data(0), next(nullptr) {};
	Object data;
	Node *next;
};

template <typename Object>
struct SglList
{
public:
	SglList() :Siz(0) { header = new Node<Object>; };
	SglList(SglList &sgl) :Siz(sgl.Siz) { delete header; header = sgl.header; };
	Node<Object>* Found(Object x);//return the node prior to which contains x
	Node<Object>* FindPos(Object x);//return the node prior to which > x
	SglList &Add(Object x);//if x not exits, insert it
	SglList &Rmov(Object x);//if x exits, remove it
	//SglList &Revse();
	void Print();
	size_t size() { return Siz; };
private:
	size_t Siz;
	Node<Object> *header;
};

template <typename Object>
void SglList<Object>::Print()
{
	Node<Object> *itr = header->next;
	for (; itr != nullptr; itr = itr->next)
		cout << itr->data << " ";
	cout << endl;
}

template <typename Object>
Node<Object>* SglList<Object>::Found(Object x)
{
	Node<Object> *itr = header->next;
	Node<Object> *prv = header;
	while (itr != nullptr)
	{
		if (itr->data == x)
			return prv;
		prv = itr;
		itr = itr->next;
	}
	return nullptr;
}

template <typename Object>
Node<Object>* SglList<Object>::FindPos(Object x)
{
	Node<Object> *itr = header->next;
	Node<Object> *prv = header;
	while (itr != nullptr)
	{
		if (itr->data > x)
			return prv;
		prv = itr;
		itr = itr->next;
	}
	return prv;
}

template <typename Object>
SglList<Object>& SglList<Object>::Add(Object x)
{
	if (!Found(x))
	{
		Node<Object> *temp = new Node<Object>;
		temp->data = x;
		Node<Object> *p = FindPos(x);
		temp->next = p->next;
		p->next = temp;
	}
	else cout << x << " already exits" << endl;
	return *this;
}

template <typename Object>
SglList<Object> &SglList<Object>::Rmov(Object x)
{
	Node<Object> *p = Found(x);
	if (p)
	{
		Node<Object> *temp = p->next;
		p->next = p->next->next;
		delete temp;
	}
	else cout << x << " not found" << endl;
	return *this;
}
int main()
{
	SglList<int> set;
	//set.Add(1).Add(2).Add(3).Add(4); set.Print();
	//set.Add(2).Add(0).Add(5).Add(3); set.Print();
	//set.Rmov(8).Rmov(1).Rmov(4).Rmov(10); set.Print();

	int arr[]{2, 1, 7, 4, 9, 3, 8, 10, 5, 6};

	for (auto i = 0; i < 10; ++i)
	{
		cout << arr[i] << " ";
		set.Add(arr[i]);
	}
	cout << endl;
	set.Print();
	return 0;
}

