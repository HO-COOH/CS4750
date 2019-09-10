#pragma once
#include <array>
#include <utility>
#include <vector>
class State
{
	std::array<std::array<bool, 5>, 5> map;	//true->cleaned, false->dirty
	std::pair<int, int> position;
	double cost = 0.0;
public:
	State(std::pair<int, int> initial_position);					//initially every place on the map is cleaned
	void init_map(std::vector<std::pair<int, int>>dirty_position);	//init with dirty locations

	/*Movements*/
	void moveUp()
	{
		cost -= 1.2;
		if (position.first != 0)
			position.first -= 1;
	}
	void moveDown()
	{
		cost -= 1.3;
		if (position.first != 4)
			position.first += 1;
	}
	void moveLeft()
	{
		cost -= 1.0;
		if (position.second != 0)
			position.second -= 1;
	}
	void moveRight()
	{
		cost -= 1.1;
		if (position.second != 4)
			position.second += 1;
	}

	/*Actions*/
	void suck()
	{
		cost -= 0.2;
		if (map[position.first][position.second] == false)
		{
			map[position.first][position.second] == true;
			cost += 4.0;
		}
	}
	void noOp()
	{
	}

	/*Performance*/
	double getCost() const
	{
		return cost;
	}

	auto getState() const
	{
		return std::make_pair(map,position);
	}
};

void UniformTreeSearch(State& state);
void UniformGraphSearch(State& state);
void DepthFirstTreeSearch(State& state);
void DepthFirstGraphSearch(State& state);

