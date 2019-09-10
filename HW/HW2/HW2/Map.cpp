#include "Map.h"
State::State(std::pair<int, int> initial_position):position(initial_position)
{
	for (auto& row : map)
	{
		std::fill(row.begin(), row.end(), true);
	}
}

void State::init_map(std::vector<std::pair<int, int>>dirty_position)
{
	for (auto& each_position : dirty_position)
	{
		map[each_position.first][each_position.second] = false;
	}
}

void UniformTreeSearch(State& state)
{

}