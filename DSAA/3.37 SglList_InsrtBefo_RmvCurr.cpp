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
	Node<Object>* Find(Object x);//return the node prior to which contains x
	SglList &Add(Object x);//if x not exits, insert it
	SglList &Rmov(Object x);//if x exits, remove it
	void Print();
	size_t size() { return Siz; };

	Node<Object> *InsrtBefo(Object x, Node<Object> *node);//insert x before node and return it
	Node<Object> *RmovCurr(Node<Object> *node);//remove node, return rear node

public:
	size_t Siz;
	Node<Object> *header;
};

//only knowing node, insert x before node
//copy node->next->data to node
//copy node and insert after node
template <typename Object>
Node<Object> * SglList<Object>::InsrtBefo(Object x, Node<Object> *node)
{
	Node<Object> *temp = new Node<Object>;
	temp->data = node->data;
	temp->next = node->next;
	node->data = x;
	node->next = temp;
	return node;
}

template <typename Object>
Node<Object> * SglList<Object>::RmovCurr(Node<Object> *node)
{
	Node<Object> *temp;
	temp = node->next;
	node->data = node->next->data;
	node->next = node->next->next;
	delete temp;
	return node;
}

template <typename Object>
void SglList<Object>::Print()
{
	Node<Object> *itr = header->next;
	for (; itr != nullptr; itr = itr->next)
		cout << itr->data << " ";
	cout << endl;
}

template <typename Object>
Node<Object>* SglList<Object>::Find(Object x)
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
SglList<Object>& SglList<Object>::Add(Object x)
{
	if (!Find(x))
	{
		Node<Object> *temp = new Node<Object>;
		temp->data = x;
		temp->next = header->next;
		header->next = temp;
	}
	else cout << x << " already exits" << endl;
	return *this;
}

template <typename Object>
SglList<Object> &SglList<Object>::Rmov(Object x)
{
	Node<Object> *p = Find(x);
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
	for (auto i = 1; i <= 20; ++i)
		set.Add(2*i);
	set.Print();
	Node<int> *p=set.header->next;
	int i = 1;
	while (i <= 20 && p)
	{
		p=set.InsrtBefo(2 * i - 1, p);
		++i; p = p->next->next;
	}
	set.Print();
	p = set.header->next;
	//the following {} moves p 2 steps foward, thus p->next->next must be meaningful
	while (p->next->next) 
	{
		p = p->next;
		p = set.RmovCurr(p);
	}
	set.Print();

	return 0;
}

