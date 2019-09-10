#include "Map.h"
#include <iostream>

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

void ExpandState(State& state, std::vector<decltype(state.getState())>& fringe)
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

	fringe.push_back(left.getState());
	fringe.push_back(right.getState());
	fringe.push_back(up.getState());
	fringe.push_back(down.getState());
	fringe.push_back(noop.getState());
	fringe.push_back(suck.getState());
}

size_t FindMinCost(const std::vector<std::tuple<std::array<std::array<bool, 5>, 5>, std::pair<int, int>, double>>& fringe)
{
	size_t index = 0;
	size_t i = 1;
	for (auto it = fringe.begin()+1; it != fringe.end(); ++it)
	{
		if (std::get<2>(*it) < std::get<2>(fringe[index]))
			index = i;
		++i;
	}
	return index;
}

void UniformTreeSearch(State& state)
{
	State initial_state(state);
	std::vector<decltype(state.getState())> fringe;
	fringe.push_back(initial_state.getState());
	size_t depth = 0;
	while (depth != 10)
	{
		std::cout <<depth<<" "<< fringe.size()<<std::endl;
		if (fringe.empty())
		{
			std::cout << "Search failure!\n";
			return;
		}
		auto minCostIndex = FindMinCost(fringe);
		State temp(fringe[minCostIndex]);
		fringe.erase(fringe.begin() + minCostIndex);
		ShowMove(temp);
		ExpandState(temp, fringe);
		++depth;
	}
}

void UniformGraphSearch(State& state)
{
}

void DepthFirstTreeSearch(State& state)
{
}

void DepthFirstGraphSearch(State& state)
{
}


void ShowMove(const State& state)
{
	using std::cout;
	auto& movements = state.getMove();
	for (auto& each_move : movements)
	{
		switch (each_move)
		{
		case 0:cout << "¡ü";
		case 1:cout << "¡ý";
		case 2:cout << "¡û";
		case 3:cout << "¡ú";
		case 4:cout << "S";
		case 5:cout << "O";
		default:
			cout << "Error in movement!\n";
			return;
		}
	}
}