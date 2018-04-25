#include <iostream>
#include <vector>
using namespace std;

struct Index
{
	int first{ 0 }, last{ 0 };
};

struct Node
{
	int val{ 0 }, pos{ 0 };
	Node *prev{ NULL }, *next{ NULL };
};

struct IncQue
{
	Node *head, *tail;
	IncQue() { head = new Node; tail = new Node; head->next = tail; tail->prev = head; }
	void pop_front();
	void push_back(int x, int pos);
};

void IncQue::pop_front()
{
	head->next = head->next->next;
	head->next->prev = head;
}

void IncQue::push_back(int x, int pos)
{
	Node *new_node = new Node;
	new_node->val = x;
	new_node->pos = pos;
	Node *p = tail->prev;
	while (p != head && p->val > x)
		p = p->prev;
	p->next = new_node;
	new_node->prev = p;
	new_node->next = tail;
	tail->prev = new_node;
}

struct DecQue
{
	Node *head, *tail;
	DecQue() { head = new Node; tail = new Node; head->next = tail; tail->prev = head;}
	void pop_front();
	void push_back(int x, int pos);
};

void DecQue::pop_front()
{
	head->next = head->next->next;
	head->next->prev = head;
}

void DecQue::push_back(int x, int pos)
{
	Node *new_node = new Node;
	new_node->val = x;
	new_node->pos = pos;
	Node *p = tail;
	while (p != head && p->val < x)
		p = p->prev;
	p->next = new_node;
	new_node->prev = p;
	new_node->next = tail;
	tail->prev = new_node;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k, *h;
	cin >> n >> k;
	h = new int[n + 2]; h[n + 1] = 2000000000;
	for (int i = 1; i <= n; ++i)
		cin >> h[i];

	vector<Index> idx;
	IncQue inc; DecQue dec;
	int left{ 1 }, right{ 0 };
	int min{ 0 }, max{ 0 };
	int max_num_book{ 0 };
	while (right <= n)
	{
		while (max - min <= k && right <= n)
		{
			++right;
			inc.push_back(h[right],right);
			dec.push_back(h[right],right);
			min = inc.head->next->val;
			max = dec.head->next->val;
		}
		if (right - left >= max_num_book)
		{
			if (right - left > max_num_book)
			{
				max_num_book = right - left;
				idx.clear();
			}
			Index new_idx;
			new_idx.first = left;
			new_idx.last = right - 1;
			idx.push_back(new_idx);
		}
		if(inc.head->next->pos == left)
			inc.pop_front();
		if (dec.head->next->pos == left)
			dec.pop_front();
		++left;
		min = inc.head->next->val;
		max = dec.head->next->val;
	}
	cout << max_num_book << ' ' << idx.size() << endl;
	for (auto i : idx)
		cout << i.first << ' ' << i.last << endl;
	return 0;
}
