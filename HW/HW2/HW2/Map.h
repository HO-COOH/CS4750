#pragma once
#include <array>
#include <utility>
#include <vector>
#include <tuple>
class State
{
	std::array<std::array<bool, 5>, 5> map;	//true->cleaned, false->dirty
	std::pair<int, int> position;
	double cost = 0.0;
	std::vector<short> movement;
public:
	State(std::pair<int, int> initial_position);					//initially every place on the map is cleaned
	State(std::tuple<std::array<std::array<bool, 5>,5>, std::pair<int, int>, double> state);
	void init_map(std::vector<std::pair<int, int>>dirty_position);	//init with dirty locations

	/*Movements*/
	void moveUp()
	{
		cost -= 1.2;
		movement.push_back(0);
		if (position.first != 0)
			position.first -= 1;
	}
	void moveDown()
	{
		cost -= 1.3;
		movement.push_back(1);
		if (position.first != 4)
			position.first += 1;
	}
	void moveLeft()
	{
		cost -= 1.0;
		movement.push_back(2);
		if (position.second != 0)
			position.second -= 1;
	}
	void moveRight()
	{
		cost -= 1.1;
		movement.push_back(3);
		if (position.second != 4)
			position.second += 1;
	}

	/*Actions*/
	void suck()
	{
		cost -= 0.2;
		movement.push_back(4);
		if (map[position.first][position.second] == false)
		{
			map[position.first][position.second] = true;
			cost += 4.0;
		}
	}
	void noOp()
	{
		movement.push_back(5);
	}

	/*Performance*/
	double getCost() const
	{
		return cost;
	}

	auto getState() const
	{
		return std::make_tuple(map, position, cost);
	}

	auto& getMove() const
	{
		return movement;
	}
};

void UniformTreeSearch(State& state);
void UniformGraphSearch(State& state);
void DepthFirstTreeSearch(State& state);
void DepthFirstGraphSearch(State& state);

void ShowMove(const State& state);