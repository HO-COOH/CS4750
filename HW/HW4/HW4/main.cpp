#include "Node.h"
#include <iostream>

using namespace std;

void Play(State s)
{
	cout << "Initial state: " << s << endl;
	size_t index = 0;
	do {
		cout << "Take 1 or 2? -> ";
		unsigned int num;
		cin >> num;
		cout << "Which pile? (starts from 0) -> ";
		size_t pile;
		cin >> pile;
		if (pile >= s.piles())
		{
			cout << "Error pile index! Should be 0-" << s.piles() - 1 <<"Retry!\n";
			continue;
		}
		switch (num)
		{
		case 1:
			if (!s.takeOne(pile))
			{
				cout << "Operation failed. Retry!\n";
				abort();
			}
			break;
		case 2:
			if (!s.takeTwo(pile))
			{
				cout << "Operation failed. Retry!\n";
				abort();
			}
			break;
		default:
			cout << "Error!Enter 1 or 2! Retry\n";
		}
		s.printSteps(index++);
		if (s.isOver())
		{
			cout << "\nYou lose!\n";
			return;
		}
		else
		{
			cout << endl;
			s = MiniMaxSearch(s, MIN, index);
			s.printSteps(index++);
		}
	} while (!s.isOver());
	cout << "\nYou win!\n";
}

int main()
{
	Play(State({ 3,4,5 }));
	cout << "\n\nNew round:\n";
	Play(State({ 2,3,4,5 }));
	cout << "\n\nFinished!\n";
}