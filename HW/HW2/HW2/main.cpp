#include <iostream>
#include <iterator>
#include <vector>
#include "Map.h"

using namespace std;

void Test0()
{
	vector<int>a { 3, 6, 1, 2, 1};
	cout << a.size()<<endl;
	a.erase(a.begin() + 2);
	cout << a.size();
}

void Test1()
{
	using loc=pair<int, int>;
	loc init_pos(2, 1);

	vector<loc> dirty_pos;
	dirty_pos.reserve(12);
	dirty_pos.emplace_back(loc(0, 0));
	dirty_pos.emplace_back(loc(0, 3));
	dirty_pos.emplace_back(loc(0, 4));
	dirty_pos.emplace_back(loc(1, 0));
	dirty_pos.emplace_back(loc(1, 3));
	dirty_pos.emplace_back(loc(1, 3));
	dirty_pos.emplace_back(loc(2, 4));
	dirty_pos.emplace_back(loc(3, 0));
	dirty_pos.emplace_back(loc(3, 2));
	dirty_pos.emplace_back(loc(4, 0));
	dirty_pos.emplace_back(loc(4, 3));
	dirty_pos.emplace_back(loc(4, 4));

	State t1(init_pos);
	t1.init_map(dirty_pos);

	UniformTreeSearch(t1);
}

int main()
{
	//Test0();
	Test1();

}