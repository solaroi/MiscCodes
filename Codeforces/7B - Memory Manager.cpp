#include <iostream>
#include <string>
using namespace std;

struct Block
{
	int id;
	int left, right;
	Block *next{ NULL };
	Block(int i = 0, int l = 0, int r = 0) { id = i; left = l; right = r; };
};

struct Memory
{
	Block *head, *tail;
	int max_id;
	Memory(int n = 0);
	Block* find_free(int n);
	int alloc(Block* p, int n);
	Block* find(int id);
	bool del(Block *p);
	void defrag();
};

Memory::Memory(int n)
{
	head = new Block(0, 0, 0);
	tail = new Block(0, n, n);
	head->next = tail;
	max_id = 0;
}

Block* Memory::find_free(int n)
{
	Block *p = head;
	while (p != tail && (p->next->left - p->right) < n)
		p = p->next;
	return p == tail ? NULL : p;
}

int Memory::alloc(Block* p, int n)
{
	int id = ++max_id;
	Block *new_block = new Block(id, p->right, p->right + n);
	new_block->next = p->next;
	p->next = new_block;
	return id;
}

Block* Memory::find(int id)
{
	Block *p = head;
	while (p->next != tail && (p->next->id != id))
		p = p->next;
	return p->next == tail ? NULL : p;
}

bool Memory::del(Block *p)
{
	if (p->next == NULL)
		return false;
	else
	{
		p->next = p->next->next;
		return true;
	}
}

void Memory::defrag()
{
	Block *p = head;
	while (p->next != tail)
	{
		if (p->next->left > p->right)
		{
			p->next->right -= (p->next->left - p->right);
			p->next->left = p->right;
		}
		p = p->next;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	string opt; 
	Memory mem(m);
	for (int i = 0; i < n; ++i)
	{
		cin >> opt;
		if (opt[0] == 'a')
		{
			int opr;
			cin >> opr;
			Block *p = mem.find_free(opr);
			if (p == NULL)
				cout << "NULL" << endl;
			else
				cout << mem.alloc(p, opr) << endl;
		}
		else if (opt[0] == 'e')
		{
			int id;
			cin >> id;
			Block *p = mem.find(id);
			if (p == NULL)
				cout << "ILLEGAL_ERASE_ARGUMENT" << endl;
			else mem.del(p);
		}
		else
			mem.defrag();
	}
	return 0;
}
