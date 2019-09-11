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
	dirty_pos.emplace_back(loc(1, 4));
	dirty_pos.emplace_back(loc(2, 4));
	dirty_pos.emplace_back(loc(3, 0));
	dirty_pos.emplace_back(loc(3, 2));
	dirty_pos.emplace_back(loc(4, 0));
	dirty_pos.emplace_back(loc(4, 3));
	dirty_pos.emplace_back(loc(4, 4));

	State t1(init_pos);
	t1.init_map(dirty_pos);

	cout << "--------------------Test Case 1-----------------------" << endl;
	cout << "--------------------Runing Uniform Cost Tree Search-----------------------"<<endl;
	UniformTreeSearch(t1);

	cout << "--------------------Runing Uniform Cost Graph Search-----------------------" << endl;
	UniformGraphSearch(t1);

	cout << "--------------------Runing Depth First Tree Search-----------------------" << endl;
	DepthFirstTreeSearch(t1);

	cout << "--------------------Runing Depth First Graph Search-----------------------" << endl;
	DepthFirstGraphSearch(t1);
}

void Test2()
{
	using loc=pair<int, int>;
	loc init_pos(2, 2);

	vector<loc> dirty_pos;
	dirty_pos.reserve(8);
	dirty_pos.emplace_back(loc(0, 0));
	dirty_pos.emplace_back(loc(0, 2));
	dirty_pos.emplace_back(loc(1, 3));
	dirty_pos.emplace_back(loc(2, 0));
	dirty_pos.emplace_back(loc(2, 3));
	dirty_pos.emplace_back(loc(3, 0));
	dirty_pos.emplace_back(loc(3, 3));
	dirty_pos.emplace_back(loc(4, 0));

	State t2(init_pos);
	t2.init_map(dirty_pos);

	cout << "--------------------Test Case 2-----------------------" << endl;
	cout << "--------------------Runing Uniform Cost Tree Search-----------------------" << endl;
	UniformTreeSearch(t2);

	cout << "--------------------Runing Uniform Cost Graph Search-----------------------" << endl;
	UniformGraphSearch(t2);

	cout << "--------------------Runing Depth First Tree Search-----------------------" << endl;
	DepthFirstTreeSearch(t2);

	cout << "--------------------Runing Depth First Graph Search-----------------------" << endl;
	DepthFirstGraphSearch(t2);

}

int main()
{
	//Test0();
	Test1();
	cout << endl << endl;
	Test2();

}