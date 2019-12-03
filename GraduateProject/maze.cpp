#include "maze.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <chrono>
#include <array>

using namespace std;

Maze::Maze(size_t row, size_t column):rows(row), cols(column)
{
    maze.resize(row);
    size_t rowIndex=0;
    for (auto& each_row : maze)
    {
        each_row.resize(column);
        fill(each_row.begin(), each_row.end(), rowIndex==0||rowIndex==column-1? false: true);
        each_row[0] = false;                                    //left side
        each_row[column - 1] = false;                             //right side
        ++rowIndex;
    }
}

void _Generate_Recursive(Maze& maze, const std::pair<size_t, size_t> upleft, const std::pair<size_t, size_t> bottomright)
{
    size_t rows = bottomright.first - upleft.first + 1;
    size_t cols = bottomright.second - upleft.second + 1;
    if (rows < 2 || cols < 2)
        return;

    //fill the horizontal wall
    size_t wall_horizontal = Random_Num(upleft.first + 1, bottomright.first - 1);
    std::fill_n(maze.maze[wall_horizontal].begin() + (upleft.second), cols, false);

    //fill the vertical wall
    size_t wall_vertical = Random_Num(upleft.second + 1, bottomright.second - 1);
    for (size_t row = upleft.first; row < bottomright.first + 1; ++row)
        maze.maze[row][wall_vertical] = false;

    //randomly choose 3 holes in 3 of the walls
    enum wall { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };
    size_t non_hole = Random_Num(0, 3);
    for (size_t i = 0; i < 4; ++i)
    {
        if (i == non_hole)
            continue;
        else
        {
            switch (i)
            {
            case (wall::LEFT):
            {
                maze.maze[wall_horizontal][Random_Num(upleft.second, wall_vertical - 1)] = true;
                break;
            }
            case (wall::RIGHT):
            {
                maze.maze[wall_horizontal][Random_Num(wall_vertical + 1, bottomright.second)] = true;
                break;
            }
            case (wall::UP):
            {
                maze.maze[Random_Num(upleft.first, wall_horizontal - 1)][wall_vertical] = true;
                break;
            }
            case (wall::DOWN):
            {
                maze.maze[Random_Num(wall_horizontal + 1, bottomright.first)][wall_vertical] = true;
                break;
            }
            default:
                cerr << "Logic error happened in generating holes!\n";
            }
        }
    }

    using position = pair<size_t, size_t>;
    array< pair<position, position>, 4> spaces //each space is a pair of <upleft, bottomright>
    {
        pair{ upleft, pair{wall_horizontal - 1, wall_vertical - 1} },
        {{upleft.first,wall_vertical + 1}, {wall_horizontal - 1, bottomright.second} },
        {{wall_horizontal + 1, upleft.second}, {bottomright.first, wall_vertical - 1}},
        {{wall_horizontal + 1, wall_vertical + 1}, bottomright}
    };
    for (const auto& space : spaces)
        _Generate_Recursive(maze, space.first, space.second);
}

enum class direction_last{horizontal, vertical, none};
struct last_wall
{
    direction_last direction;
    size_t index;
    size_t hole;
};
void _Generate_Recursive2(Maze& maze, const std::pair<size_t, size_t> upleft, const std::pair<size_t, size_t> bottomright, const last_wall& last_wall)
{
    size_t rows = bottomright.first - upleft.first+1;
    size_t cols = bottomright.second - upleft.second+1;
    if (rows < 3 || cols < 3)
        return;
    if (rows >= cols) //add a horizontal wall
    {
        size_t wall_horizontal = Random_Num(upleft.first+1 , bottomright.first-1 );
        std::fill_n(maze.maze[wall_horizontal].begin() + (upleft.second), cols, false);
        //randomly add a hole in the horizontal wall
        size_t hole;
        if(last_wall.direction==direction_last::vertical && wall_horizontal==last_wall.hole)
        {
            if(bottomright.second<last_wall.index)
                hole=last_wall.index-1;
            else
                hole=last_wall.index+1;
            maze.maze[wall_horizontal][hole]=true;
        }
        else
        {
            hole=Random_Num(upleft.second, bottomright.second);
            maze.maze[wall_horizontal][hole] = true;
        }
        //now the space is divided to 2 parts, recursively call the function
        _Generate_Recursive2(maze, upleft, { wall_horizontal - 1, bottomright.second }, {direction_last::horizontal, wall_horizontal, hole});
        _Generate_Recursive2(maze, { wall_horizontal + 1, upleft.second }, bottomright, {direction_last::horizontal, wall_horizontal, hole});
    }
    else    //add a vertical wall
    {
        size_t wall_vertical = Random_Num(upleft.second+1, bottomright.second-1);
        for (size_t row = upleft.first; row < bottomright.first + 1; ++row)
            maze.maze[row][wall_vertical] = false;
        //randomly add a hole in the horizontal wall
        size_t hole;
        if(last_wall.direction==direction_last::horizontal && wall_vertical==last_wall.hole)
        {
            if(bottomright.first<last_wall.index)
                hole=last_wall.index-1;
            else
                hole=last_wall.index+1;
            maze.maze[hole][wall_vertical]=true;
        }
        else
        {
            hole=Random_Num(upleft.first, bottomright.first);
            maze.maze[hole][wall_vertical] = true;
        }
        //now the space is divided to 2 parts, recursively call the function
        _Generate_Recursive2(maze, upleft, { bottomright.first, wall_vertical - 1 }, {direction_last::vertical, wall_vertical, hole});
        _Generate_Recursive2(maze, { upleft.first, wall_vertical + 1 }, bottomright, {direction_last::vertical, wall_vertical, hole});
    }
}

void _Generate_Recursive3(Maze& maze, const std::pair<size_t, size_t> upleft, const std::pair<size_t, size_t> bottomright, vector<vector<bool>>&holes)
{
	int rows = bottomright.first - upleft.first + 1;
	int cols = bottomright.second - upleft.second + 1;
	if (rows < 3 || cols < 3)
		return;
	if (rows >= cols) //add a horizontal wall
	{
		size_t wall_horizontal = Random_Num(upleft.first + 1, bottomright.first - 1);
		std::fill_n(maze.maze[wall_horizontal].begin() + (upleft.second), cols, false);
		//randomly add a hole in the horizontal wall
		size_t hole = Random_Num(upleft.second, bottomright.second);
		maze.maze[wall_horizontal][hole] = true;
		holes[wall_horizontal][hole] = true;
		if (holes[wall_horizontal][upleft.second - 1])
			maze.maze[wall_horizontal][upleft.second] = true;
		if (holes[wall_horizontal][bottomright.second + 1])
			maze.maze[wall_horizontal][bottomright.second] = true;

		//now the space is divided to 2 parts, recursively call the function
		_Generate_Recursive3(maze, upleft, { wall_horizontal - 1, bottomright.second }, holes);
		_Generate_Recursive3(maze, { wall_horizontal + 1, upleft.second }, bottomright, holes);
	}
	else    //add a vertical wall
	{
		size_t wall_vertical = Random_Num(upleft.second + 1, bottomright.second - 1);
		for (size_t row = upleft.first; row < bottomright.first + 1; ++row)
			maze.maze[row][wall_vertical] = false;
		//randomly add a hole in the horizontal wall
		size_t hole = Random_Num(upleft.first, bottomright.first);
		maze.maze[hole][wall_vertical] = true;
		holes[hole][wall_vertical] = true;
		if (holes[upleft.first-1][wall_vertical])
			maze.maze[upleft.first][wall_vertical] = true;
		if (holes[bottomright.first+1][wall_vertical])
			maze.maze[bottomright.first][wall_vertical] = true;
		//now the space is divided to 2 parts, recursively call the function
		_Generate_Recursive3(maze, upleft, { bottomright.first, wall_vertical - 1 }, holes);
		_Generate_Recursive3(maze, { upleft.first, wall_vertical + 1 }, bottomright, holes);
	}
}

void Maze::Generate()
{
	vector<vector<bool>> holes(rows);
	for (auto& each_row : holes)
	{
		each_row.resize(cols);
		fill(each_row.begin(), each_row.end(), false);
	}
	_Generate_Recursive3(*this, { 1,1 }, { maze.size() - 2, maze[1].size() - 2 }, holes);
}

bool Maze::ToText(std::string_view fileName) const
{
    ofstream file(fileName.data());
    if (!file.is_open())
    {
        cerr << "Maze -> Text file open failed!\n";
        return false;
    }
    for (const auto& each_row : maze)
    {
        copy(each_row.begin(), each_row.end(), ostream_iterator<char>(file));
        file << '\n';
    }
    file.close();
    return true;
}

void Maze::Show() const
{
    for (const auto& each_row : maze)
    {
        for (auto value : each_row)
        {
            if (!value)
                cout << '0';
            else
                cout << ' ';
        }
        cout << '\n';
    }
}

size_t Random_Num(size_t min, size_t max)
{
    static mt19937 engine{ static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()) };
    uniform_int_distribution<size_t> generator(min, max);
    return generator(engine);
}

