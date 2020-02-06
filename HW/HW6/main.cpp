#include "3SAT.h"
#include <iostream>
#include "Timer.h"
#include <thread>

using namespace std;

void Test0()
{
	Timer t;
	cout << "\nTest case 0:\n";
	Three_SAT test0("testCase0.cnf");
	BacktrackingSearch(test0);
}

void Test4()
{
	Timer t;
	cout << "\nTest case 0:\n";
	Three_SAT test0("testCase4.cnf");
	BacktrackingSearch(test0);
}

void Test1()
{
	Timer t;
	cout << "\nTest case 1:\n";
	Three_SAT test0("testCase1.cnf");
	BacktrackingSearch(test0);
}

void Test2()
{
	Timer t;
	cout << "\nTest case 2:\n";
	Three_SAT test0("testCase2.cnf");
	BacktrackingSearch(test0);
}


int main()
{
	//Test0();
	//Test4();
	Test1();
	Test2();
	//thread t1(Test1);
	//thread t2(Test2);
	//t1.join();
	//t2.join();
}