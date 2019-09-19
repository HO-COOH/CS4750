#include "Map.h"
#include "Timer.h"
#include <iostream>
#include <stack>
#include <random>
#include <chrono>
#include <queue>

std::random_device rd;
State::State(std::pair<int, int> initial_position):position(initial_position)
{
	for (auto& row : map)
	{
		std::fill(row.begin(), row.end(), true);
	}
}

State::State(std::tuple<std::array<std::array<bool, 5>,5>, std::pair<int, int>, double> state):map(std::get<0>(state)), position(std::get<1>(state)), cost(std::get<2>(state))
{

}

void State::init_map(std::vector<std::pair<int, int>>dirty_position)
{
	for (auto& each_position : dirty_position)
	{
		map[each_position.first][each_position.second] = false;
	}
}

bool State::operator==(const State& state2) const
{
	for (size_t row = 0; row != 5; ++row)
	{
		for (size_t col = 0; col != 5; ++col)
		{
			if (map[row][col] != state2.map[row][col])
				return false;
		}
	}
	if (position.first != state2.position.first || position.second != state2.position.second)
		return false;
	return true;
}

void ExpandState(const State& state, std::vector<State>& fringe, bool graph=false)
{
	State left(state);
	left.moveLeft();

	State right(state);
	right.moveRight();

	State up(state);
	up.moveUp();

	State down(state);
	down.moveDown();

	State noop(state);
	noop.noOp();

	State suck(state);
	suck.suck();

		fringe.push_back(left);
		fringe.push_back(right);
		fringe.push_back(up);
		fringe.push_back(down);
		fringe.push_back(suck);
		if (!graph)
			fringe.push_back(noop);

}

size_t FindMaxPerf(const std::vector<State>& fringe)
{
	size_t index = 0;
	size_t i = 1;
	for (auto it = fringe.begin()+1; it != fringe.end(); ++it)
	{
		if (it->getCost()>fringe[index].getCost())
			index = i;
		++i;
	}
	return index;
}

auto FindMaxPerf(const std::stack<State>& fringe)
{
	std::stack<State> temp(fringe);
	State max = temp.top();
	temp.pop();
	for (State current = temp.top(); !temp.empty(); temp.pop())
	{
		if (current.getCost() > max.getCost())
			max = current;
	}
	return max;
}

bool IfExpandedToDepth(const std::vector<State>& fringe, size_t depth)
{
	for (auto iter = fringe.begin(); iter != fringe.end(); ++iter)
	{
		if (iter->movementsNumber() < 10)
			return false;
	}
	return true;
}

/*Slow as fuck implementation (using std::make_heap) */
//This was my original implementation, let's add a suffix for it
void UniformTreeSearch_Bad(const State& state)
{
	using namespace std;
	Timer t;
	cout << "The first 5 nodes to be expand are:\n";
	vector<State> fringe;
	fringe.push_back(state);
	State maxPerfState = state;
	size_t index = 0;
	size_t expansion = 0;
	make_heap(fringe.begin(), fringe.end());
	while (!fringe.empty())
	{
		if (maxPerfState < fringe.front())
			maxPerfState = fringe.front();
		if (index++ < 5)
			ShowMove(fringe.front());
		if (fringe.front().movementsNumber() < 6)
		{
			vector<State> expandedNodes;
			ExpandState(fringe.front(), expandedNodes);
			expansion += 6;
			fringe.erase(fringe.begin());
			for (auto& each_node : expandedNodes)
			{
				fringe.push_back(each_node);
				push_heap(fringe.begin(), fringe.end());
			}
		}
		else
			fringe.erase(fringe.begin());			
	}
	std::cout << "Total expansion= " << expansion << std::endl;
	std::cout << "\nThe best performance within 10 movements is:\n";
	ShowMove(maxPerfState);
}

/*Much faster implementation (using std::priority_queue)*/
void UniformTreeSearch(const State& state)
{
	using namespace std;
	Timer t;
	cout << "The first 5 nodes to be expand are:\n";
	priority_queue<State> fringe;
	fringe.push(state);
	State maxPerfState = state;
	size_t index = 0;
	size_t expansion = 0;
	while (!fringe.empty())
	{
		if (maxPerfState < fringe.top())
			maxPerfState = fringe.top();
		if (index++ < 5)
			ShowMove(fringe.top());
		if (fringe.top().movementsNumber() < 10)
		{
			vector<State> expandedNodes;
			ExpandState(fringe.top(), expandedNodes);
			expansion += 6;
			fringe.pop();
			for (auto& each_node : expandedNodes)
				fringe.push(each_node);
		}
		else
			fringe.pop();
	}
	std::cout << "Total expansion= " << expansion << std::endl;
	std::cout << "\nThe best performance within 10 movements is:\n";
	ShowMove(maxPerfState);
}

/*A helper function to check whether the state is visited*/
//param: state -the state to check
//param: visited -the vector containing all visited states
bool IsVisited(const std::vector<State>& visited, const State& state)
{
	for (auto& visited_state : visited)
	{
		if (visited_state == state)
			return true;
	}
	return false;
}

/*Ununsed helper function*/

//auto GetRidOfVisited(const std::vector<State>& visited, std::vector<State>& expandedNodes)
//{
//	if (expandedNodes.empty() || visited.empty())
//		return std::vector<State>();
//	std::vector<State> expandedNoneVisitedNodes;
//	expandedNoneVisitedNodes.reserve(expandedNodes.size());
//	for (auto& each_node : expandedNodes)
//	{
//		if (!IsVisited(visited, each_node))
//			expandedNoneVisitedNodes.push_back(each_node);
//	}
//	return expandedNoneVisitedNodes;
//}


/*This is also using std::make_heap with std::vector, but it is performing well because of much fewer nodes generated*/
void UniformGraphSearch_Bad(const State& state)
{
	using namespace std;
	Timer t;
	cout << "The first 5 nodes to be expand are:\n";
	vector<State> fringe;
	vector<State> visited;
	fringe.push_back(state);
	State maxPerfState = state;
	size_t index = 0;
	size_t expansion = 0;
	make_heap(fringe.begin(), fringe.end());
	while (!fringe.empty())
	{
		if (maxPerfState < fringe.front())
			maxPerfState = fringe.front();
		if (index++ < 5)
			ShowMove(fringe.front());
		if (fringe.front().movementsNumber() < 10)
		{
			vector<State> expandedNodes;
			ExpandState(fringe.front(), expandedNodes);
			visited.push_back(fringe.front());
			fringe.erase(fringe.begin());
			for (auto& each_node : expandedNodes)
			{
				if (IsVisited(visited, each_node))
					continue;
				else
				{
					fringe.push_back(each_node);
					push_heap(fringe.begin(), fringe.end());
					++expansion;
				}
			}
		}
		else
			fringe.erase(fringe.begin());
	}
	std::cout << "Total expansion= " << expansion << std::endl;
	std::cout << "\nThe best performance within 10 movements is:\n";
	ShowMove(maxPerfState);
}

/*A revised version (using std::priority_queue) */
void UniformGraphSearch(const State& state)
{
	using namespace std;
	Timer t;
	cout << "The first 5 nodes to be expand are:\n";
	priority_queue<State> fringe;
	vector<State> visited;
	fringe.push(state);
	State maxPerfState = state;
	size_t index = 0;
	size_t expansion = 0;
	while (!fringe.empty())
	{
		if (maxPerfState < fringe.top())
			maxPerfState = fringe.top();
		if (index++ < 5)
			ShowMove(fringe.top());
		if (fringe.top().movementsNumber() < 10)
		{
			vector<State> expandedNodes;
			ExpandState(fringe.top(), expandedNodes);
			visited.push_back(fringe.top());
			fringe.pop();
			for (auto& each_node : expandedNodes)
			{
				if (!IsVisited(visited, each_node))
				{
					fringe.push(each_node);
					++expansion;
				}
			}
		}
		else
			fringe.pop();
	}
	std::cout << "Total expansion= " << expansion << std::endl;
	std::cout << "\nThe best performance within 10 movements is:\n";
	ShowMove(maxPerfState);
}

void DepthFirstTreeSearch(const State& state)
{
	using namespace std;
	Timer t;
	stack<State> fringe;
	fringe.push(state);
	State maxPerfState = state;
	size_t expansion = 0;
	size_t index = 0;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	cout << "The first 5 nodes to be expand are:\n";
	while (!fringe.empty())
	{
		if (maxPerfState < fringe.top())
			maxPerfState = fringe.top();
		if (index++ < 5)
			ShowMove(fringe.top());
		if (fringe.top().movementsNumber() < 10)
		{
			vector<State> expandedNodes;
			ExpandState(fringe.top(), expandedNodes);
			fringe.pop();
			expansion += 6;
			shuffle(expandedNodes.begin(), expandedNodes.end(), default_random_engine(seed));
			for (auto& each_node : expandedNodes)
				fringe.push(each_node);
		}
		else
			fringe.pop();
	}
	std::cout << "Total expansion= " << expansion << std::endl;
	std::cout << "\nThe best performance within 10 movements is:\n";
	ShowMove(maxPerfState);
}

void DepthFirstGraphSearch(const State& state)
{
	using namespace std;
	Timer t;
	stack<State> fringe;
	fringe.push(state);

	vector<State> visited;

	State maxPerfState = state;
	size_t expansion = 0;
	size_t index = 0;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	cout << "The first 5 nodes to be expand are:\n";
	while (!fringe.empty())
	{
		if (maxPerfState < fringe.top())
			maxPerfState = fringe.top();
		if (index++ < 5)
			ShowMove(fringe.top());
		if (fringe.top().movementsNumber() <=11 )
		{
			vector<State> expandedNodes;
			ExpandState(fringe.top(), expandedNodes);
			visited.push_back(fringe.top());
			fringe.pop();
			//shuffle(expandedNodes.begin(), expandedNodes.end(), default_random_engine(seed));
			for (auto& each_node : expandedNodes)
			{
				if (each_node.getCost() >= 8)
				{
					cout << "Get 8\n";
					break;
				}
				if (!IsVisited(visited, each_node))
				{
					fringe.push(each_node);
					++expansion;
				}
			}
		}
		else
			fringe.pop();
	}
	std::cout << "Total expansion= " << expansion << std::endl;
	std::cout << "\nThe best performance within 10 movements is:\n";
	ShowMove(maxPerfState);
}

//If the arrows are not properly displayed, change it into ASCII character yourself!
void ShowMove(const State& state)
{
	using std::cout;
	auto& movements = state.getMove();
	cout << "There are " << movements.size() << " movements in total.\n";
	for (auto& each_move : movements)
	{
		switch (each_move)
		{
		case 0:
			cout << "¡ü";
			break;
		case 1:
			cout << "¡ý";
			break;
		case 2:
			cout << "¡û";
			break;
		case 3:
			cout << "¡ú";
			break;
		case 4:
			cout << "+";
			break;
		case 5:
			cout << "-";
			break;
		default:
			cout << "Error in movement!\n";
			return;
		}
	}
	cout <<"\t Cost="<<state.getCost()<< std::endl;
}