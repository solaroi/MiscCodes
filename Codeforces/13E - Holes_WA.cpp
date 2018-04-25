#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

struct Hole
{
	int dest_{ 0 }, steps_{ 0 };
	Hole() = default;
	Hole(int dest, int steps): dest_(dest), steps_(steps) {};
	Hole(const Hole &h) :dest_(h.dest_), steps_(h.steps_) {};
	void operator = (const Hole &h) { dest_ = h.dest_; steps_ = h.steps_; };
};

struct DisjSet
{
	Hole *holes_;
	int *power;
	int length_, lenseg_, numseg_;
	DisjSet() = default;
	DisjSet(int len);
	void UpdateAll();
	void Update(int x);
	void Query(int x, int &dest, int &steps);
};

DisjSet::DisjSet(int len)
{
	holes_ = new Hole[len + 1];
	power = new int[len + 1];
	length_ = len;
	lenseg_ = (int)floor(sqrt(len));
	numseg_ = (int)ceil(double(len) / lenseg_);
}

void DisjSet::UpdateAll()
{

	for (int i = 0; i < numseg_ - 1; ++i)
		Update((i + 1)*lenseg_);
	Update(length_);
}

void DisjSet::Update(int x)
{
	int segment_index = (x - 1) / lenseg_;
	int segment_left_bound = segment_index*lenseg_ + 1;
	int segment_right_bound = min((segment_index + 1)*lenseg_, length_);
	for (int i = x; i >= segment_left_bound; --i)
	{
		int dest = power[i] + i;
		holes_[i].dest_ = dest;
		holes_[i].steps_ = 1;
		if (dest <= segment_right_bound)
		{
			holes_[i].dest_ = holes_[dest].dest_;
			holes_[i].steps_ += holes_[dest].steps_;
		}
	}
}

void DisjSet::Query(int x, int &dest, int &steps)
{
	steps += holes_[x].steps_;
	if (holes_[x].dest_ > length_)
	{
		dest = x;
		return;
	}
	Query(holes_[x].dest_, dest, steps);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int num_holes, num_moves;
	cin >> num_holes >> num_moves;
	DisjSet holejump(num_holes);
	for (int i = 1; i <= num_holes; ++i)
		cin >> holejump.power[i];
	holejump.UpdateAll();
	/*for (int i = 1; i <= num_holes; ++i)
		cout << holejump.holes_[i].dest_ << ' ';
	cout << endl;
	for (int i = 1; i <= num_holes; ++i)
		cout << holejump.holes_[i].steps_ << ' ';
	cout << endl;*/
	int opt_id, index;
	for (int i = 0; i < num_moves; ++i)
	{
		cin >> opt_id >> index;
		if (opt_id == 0)
		{
			cin >> holejump.power[index];
			holejump.Update(index);
		}
		else
		{
			int dest{ 0 }, steps{ 0 };
			holejump.Query(index, dest, steps);
			cout << dest << ' ' << steps << endl;
		}
	}
	return 0;
}
