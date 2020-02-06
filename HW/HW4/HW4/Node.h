#pragma once
#include <vector>
#include <iostream>
#include <iterator>

enum currentRole{MIN, MAX};

class State
{
	std::vector<unsigned> stacks;
	int value=0;
	std::vector<std::vector<unsigned>> steps;
public:
	size_t piles() const
	{
		return stacks.size();
	}

	State(std::vector<unsigned> _stacks);
	State() {}

	/*operations*/
	bool takeOne();
	bool takeTwo();
	bool takeOne(size_t index);
	bool takeTwo(size_t index);
	bool operator==(const State& s2) const;
	//bool operator<(const State& s2) const;
	bool isOver() const;

	/*point value*/
	void setValue(int _value) { value = _value; }
	int getValue() const { return value; }

	/*print stacks*/
	friend std::ostream& operator<<(std::ostream& out, const State& s);
	void printSteps(size_t index) const;
	void restoreSteps(size_t index)
	{
		stacks = steps[index];
		steps.erase(steps.begin() + index+1, steps.end());
	}
};

std::vector<State> ExpandNode(const State& s);
State MiniMaxSearch(State& initial_state, currentRole _role, size_t index);


//DEBUG
void Debug(const State& initial_state);