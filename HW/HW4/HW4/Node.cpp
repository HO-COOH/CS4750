#include "Node.h"
#include <algorithm>
#include <iterator>
#include "Timer.h"


static size_t expansion = 0;

State::State(std::vector<unsigned> _stacks)
{
	if (_stacks.empty())
		std::cout << "You can't init a state with empty stack!\n";
	else
	{
		stacks = _stacks;
	}
}

bool State::takeOne()
{
	for (auto& num : stacks)
	{
		if (num >= 1)
		{
			num -= 1;
			steps.push_back(stacks);
			return true;		//success
		}
	}
	std::cout << "There are none sticks left!\n";	//none left
	return false;
}

bool State::takeTwo()
{
	for (auto& num : stacks)
	{
		if (num >= 2)
		{
			num -= 2;
			steps.push_back(stacks);
			return true;		//success
		}
	}
	std::cout << "There are less than 2 sticks left!\n";	//<=2 left
	return false;
}

bool State::takeOne(size_t index)
{
	if (stacks[index] >= 1)
	{
		stacks[index] -= 1;
		steps.push_back(stacks);
		return true;
	}
	else
		return false;
}

bool State::takeTwo(size_t index)
{
	if (stacks[index] >= 2)
	{
		stacks[index] -= 2;
		steps.push_back(stacks);
		return true;
	}
	else
		return false;
}

bool State::operator==(const State& s2) const
{
	return std::is_permutation(stacks.begin(), stacks.end(), s2.stacks.begin(), s2.stacks.end());
}

bool State::isOver() const
{
	for (auto& value : stacks)
	{
		if (value != 0)
			return false;
	}
	return true;
}

void State::printSteps(size_t index) const
{
	std::copy(steps[index].begin(), steps[index].end(), std::ostream_iterator<unsigned, char>(std::cout, ","));
}


std::ostream& operator<<(std::ostream& out, const State& s)
{
	std::copy(s.stacks.begin(), s.stacks.end(), std::ostream_iterator<unsigned>(out, ","));
	return out;
}


//if there are none sticks left, it will return an empty vector
std::vector<State> ExpandNode(const State& s)
{
	using namespace std;
	vector<State> result;
	for (unsigned index = 0; index < s.piles(); ++index)
	{
		State temp1(s);
		if(temp1.takeOne(index))
			result.push_back(temp1);
		State temp2(s);
		if(temp2.takeTwo(index))
			result.push_back(temp2);
	}
	//make result only contains unique states
	for (int i = 0; i != result.size(); ++i)
	{
		for (int j = i + 1; j != result.size(); ++j)
		{
			if (result[i] == result[j])
			{
				result.erase(result.begin() + j);
				--j;
			}
		}
	}
	expansion += result.size();
	return result;
}

State value(const State& state, currentRole role)
{
	auto result = ExpandNode(state);
	if (result.empty())
	{
		State temp(state);
		if (role == MAX)
			temp.setValue(1);
		else
			temp.setValue(0);
		return temp;
	}
	//result isn't empty, recursive call the function
	if (role == MAX)
	{
		int max_value = -INT_MAX;
		State max_State;
		for (auto& each_node : result)
		{
			State current = value(each_node, MIN);
			if (max_value < current.getValue())
			{
				max_State = current;
				max_value= max_State.getValue();
			}
		}
		return max_State;
	}
	else	//role==MIN
	{
		int min_value = INT_MAX;
		State min_State;
		for (auto& each_node : result)
		{
			State current = value(each_node, MAX);
			if (min_value > current.getValue())
			{
				min_State = current;
				min_value=min_State.getValue();
			}
		}
		return min_State;
	}
}

/*backup*/
//int value(State& state, currentRole role)
//{
//	auto result = ExpandNode(state);
//	if (result.empty())
//		return role == MAX ? 1 : 0;
//	//result isn't empty, recursive call the function
//	if (role == MAX)
//	{
//		int max_value = -INT_MAX;
//		for (auto& each_node : result)
//		{
//			if (max_value < value(each_node, MIN))
//			{
//				max_value = value(each_node, MIN);
//			}
//		}
//		return max_value;
//	}
//	else	//role==MIN
//	{
//		int min_value = INT_MAX;
//		for (auto& each_node : result)
//		{
//			if (min_value > value(each_node, MAX))
//			{
//				min_value = value(each_node, MAX);
//			}
//		}
//		return min_value;
//	}
//}

State MiniMaxSearch(State& initial_state, currentRole _role, size_t index)
{	
	Timer t;
	expansion = 0;
	auto result = value(initial_state, _role);
	std::cout << "\nTotal expansion= " << expansion << std::endl;
	result.restoreSteps(index);
	return result;
}

void Debug(const State& initial_state)
{
	using namespace std;
	auto result = ExpandNode(initial_state);
	for (auto& each_node : result)
	{
		cout << each_node << endl;
	}
}