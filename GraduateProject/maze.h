#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string_view>

struct Maze
{
    //true -> path  false->wall
    std::vector<std::vector<bool>> maze;
    const size_t rows;
    const size_t cols;
    Maze(size_t row, size_t column);

    class Maze_Iterator
    {
    private:
        const Maze* ptr;
        size_t ele_per_row;
        size_t row;
        size_t col;
    public:
        Maze_Iterator(Maze* maze, size_t row, size_t col):ptr(maze), ele_per_row(maze->maze[0].size()), row(row), col(col) {}
        Maze_Iterator& operator++()
        {
            ++col;
            if(col==ele_per_row)
            {
                col=0;
                ++row;
            }
            return  *this;
        }
        bool operator!=(const Maze_Iterator& iter) {return row!=iter.row||col!=iter.col;}
        bool operator*() {return ptr->maze[row].operator[](col);}
    };
    Maze_Iterator begin() { return {this, 0, 0}; }
    Maze_Iterator end() { return {this, maze.size()-1, maze[0].size()}; }
    void Generate();
    bool ToText(std::string_view fileName) const;
    void Show() const;
};
size_t Random_Num(size_t min, size_t max);  //generate random number in [min, max]
void _Generate_Recursive(Maze& maze, const std::pair<size_t, size_t> upleft, const std::pair<size_t, size_t> bottomright);

#endif // MAZE_H
