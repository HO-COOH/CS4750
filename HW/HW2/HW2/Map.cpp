#include "Map.h"
#include "Timer.h"
#include <iostream>
#include <stack>
#include <random>

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

void ExpandState(State& state, std::vector<State>& fringe)
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

void UniformTreeSearch(const State& state)
{
	//State initial_state(state);
	Timer t;
	std::vector<State> fringe;
	fringe.push_back(State(state));
	size_t depth = 0;
	size_t index = 0;
	std::cout << "The first 5 nodes to be expanded:\n";
	while (depth != 10)
	{
		if (fringe.empty())
		{
			std::cout << "Search failure!\n";
			return;
		}
		auto minCostIndex = FindMaxPerf(fringe);
		State temp(fringe[minCostIndex]);
		fringe.erase(fringe.begin() + minCostIndex);
		//Show move of the first 5 nodes to be expanded
		if (index++ < 5)
			ShowMove(temp);
		ExpandState(temp, fringe);
		++depth;
	}
	std::cout << "Total expansion= " << fringe.size() << std::endl;
	std::cout << "\n\nThe best performance within " << depth << " movements is:\n";
	ShowMove(fringe[FindMaxPerf(fringe)]);
}

bool IsVisited(const std::vector<State>& visited, const State& state)
{
	for (auto& visited_state : visited)
	{
		if (visited_state == state)
			return true;
	}
	return false;
}

auto GetRidOfVisited(const std::vector<State>& visited, std::vector<State>& expandedNodes)
{
	if (expandedNodes.empty() || visited.empty())
		return std::vector<State>();
	std::vector<State> expandedNoneVisitedNodes;
	expandedNoneVisitedNodes.reserve(expandedNodes.size());
	for (auto& each_node : expandedNodes)
	{
		if (!IsVisited(visited, each_node))
			expandedNoneVisitedNodes.push_back(each_node);
	}
	return expandedNoneVisitedNodes;
}

void UniformGraphSearch(const State& state)
{
	Timer t;
	std::vector<State> fringe;
	std::vector<State> visited;
	fringe.push_back(State(state));
	//visited.push_back(State(state));
	size_t depth = 0;
	size_t index = 0;
	std::cout << "The first 5 nodes to be expanded:\n";
	while (depth != 10)
	{
		if (fringe.empty())
		{
			std::cout << "Search failure!\n";
			return;
		}
		auto minCostIndex = FindMaxPerf(fringe);
		State temp(fringe[minCostIndex]);
		if (!visited.empty())
		{
			while (IsVisited(visited, temp))
			{
				fringe.erase(fringe.begin() + minCostIndex);
				if (fringe.empty())
				{
					std::cout << "Search failure!\n";
					return;
				}
				minCostIndex = FindMaxPerf(fringe);
				temp = fringe[minCostIndex];
			}
		}
		fringe.erase(fringe.begin() + minCostIndex);
		ExpandState(temp, fringe);
		visited.push_back(temp);
		if(index++<5)
			ShowMove(temp);
		depth = temp.movementsNumber();
	}
	std::cout << "Total expansion= " << fringe.size() << std::endl;
	std::cout << "\n\nThe best performance within "<<depth<<" movements is:\n";
	ShowMove(visited[FindMaxPerf(visited)]);

}

void DepthFirstTreeSearch(const State& state)
{
	using namespace std;
	Timer t;
	stack<State> fringe;
	fringe.push(State(state));
	
	random_device rd;
	size_t depth = 0;
	size_t expansion = 0;
	size_t index = 0;
	while (depth != 10)
	{
		if(index++<5)
			ShowMove(fringe.top());
		vector<State> expandedNodes;
		ExpandState(fringe.top(), expandedNodes);
		expansion += expandedNodes.size();
		if (expandedNodes.empty())
		{
			fringe.pop();
			continue;
		}
		uniform_int_distribution<> random_int(0, expandedNodes.size() - 1);
		fringe.push(expandedNodes[random_int(rd)]);
		depth = fringe.top().movementsNumber();
	}
	std::cout << "\n\nTotal expansion= " << expansion << std::endl;
}

void DepthFirstGraphSearch(const State& state)
{
	using namespace std;
	Timer t;
	stack<State> fringe;
	fringe.push(State(state));
	vector<State> visited;
	visited.push_back(State(state));
	
	random_device rd;
	size_t depth = 0;
	size_t expansion = 0;
	size_t index = 0;
	while (depth != 10)
	{
		vector<State> expandedNodes;
		ExpandState(fringe.top(), expandedNodes);
		expandedNodes=GetRidOfVisited(visited, expandedNodes);
		if (index++ < 5)
			ShowMove(fringe.top());
		expansion += expandedNodes.size();
		if (expandedNodes.empty())
		{
			fringe.pop();
			continue;
		}
		uniform_int_distribution<> random_int(0, expandedNodes.size() - 1);
		fringe.push(expandedNodes[random_int(rd)]);
		depth = fringe.top().movementsNumber();
	}
	std::cout << "\n\nTotal expansion= " << expansion << std::endl;
	ShowMove(fringe.top());
}


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
			cout << "S";
			break;
		case 5:
			cout << "O";
			break;
		default:
			cout << "Error in movement!\n";
			return;
		}
	}
	cout << std::endl;
}