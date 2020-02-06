#pragma once
#include <ctime>
#include <iostream>
class Timer
{
	clock_t current;
public:
	Timer():current(clock())
	{
	}
	~Timer()
	{
		std::cout << "Finished in " << ((double)clock() - current) / (double)(CLOCKS_PER_SEC)<<" seconds.\n";
	}
};