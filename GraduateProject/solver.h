#ifndef SOLVER_H
#define SOLVER_H
#include "maze.h"
#include <vector>
#include <optional>
#include <queue>
#include <stack>
#include "Timer.h"
using position = std::pair<size_t, size_t>;
struct Node
{
    //using position = std::pair<size_t, size_t>;
    position _position;
    std::optional<position> upNeighbor;
    std::optional<position> downNeighbor;
    std::optional<position> leftNeighbor;
    std::optional<position> rightNeighbor;
    std::vector<position> path;
    bool operator==(const Node& r) const{return _position.first==r._position.first&&_position.second==r._position.second;}
};

struct Cost:public Node
{
    std::optional<size_t> upCost;
    std::optional<size_t> downCost;
    std::optional<size_t> leftCost;
    std::optional<size_t> rightCost;
    size_t cost=0;
	position from;
    bool operator<(const Cost& r) const
    {
        return cost>r.cost;
    }
    void operator=(const Node& node)
    {
        (*this).Node::operator=(node);
    }
};

struct Heuristic:public Cost
{
    size_t heuristic=0;
    bool operator<(const Heuristic& r) const
    {
        return cost+heuristic > r.cost+r.heuristic;
    }
    Heuristic(const Cost& node):Cost(node){}
    Heuristic(const Node& node)
    {
        _position=node._position;
        if(node.upNeighbor.has_value())
            upNeighbor=node.upNeighbor;
        if(node.downNeighbor.has_value())
            downNeighbor=node.downNeighbor;
        if(node.leftNeighbor.has_value())
            leftNeighbor=node.leftNeighbor;
        if(node.rightNeighbor.has_value())
            rightNeighbor=node.rightNeighbor;
        path=node.path;
    }
    Heuristic(){}
    void operator=(const Cost& r)
    {
        (*this).Cost::operator=(r);
    }
};
struct result;
struct step_AStar
{
	std::priority_queue<Heuristic> fringe; 
	std::priority_queue<Heuristic> expanded;
	std::vector<std::vector<bool>> visited;
};
struct step_Uniform
{

};
class Solver
{
    Maze* maze; //pointer to a maze
    size_t row; //position
    size_t col;
    
    std::vector<std::vector<std::optional<Node>>> nodes;
    std::vector<Node> solution;
    size_t ExpandNodes(std::queue<Node>&fringe, const Node& nodeToExpand, const std::vector<std::vector<bool>>& visited);
    size_t ExpandNodes(std::stack<Node>&fringe, const Node& nodeToExpand, const std::vector<std::vector<bool>>& visited);
    //size_t ExpandNodes(std::priority_queue<Cost>&fringe, const Cost& nodeToExpand, const std::vector<std::vector<bool>>& visited);
protected:
    /*helper function for determine the value of a current position(given in argument) */
    bool up(size_t row, size_t col) const {return maze->maze[row-1][col];}
    bool down(size_t row, size_t col) const {return maze->maze[row+1][col];}
    bool left(size_t row, size_t col) const {return maze->maze[row][col-1];}
    bool right(size_t row, size_t col) const {return maze->maze[row][col+1];}
    bool isNode(size_t _row, size_t _col) const;
     

public:
	bool nodesMade=false;void makeNodes();
    Solver(Maze* _maze) :maze(_maze), row(1), col(1), nodesMade(false) {if(!_maze) abort();}
    auto& getNodes() const {return nodes;}
    result BreadthFirstSearch();
    result DepthFirstSearch();
    result AStarSearch();
    result UniformSearch();	
	/*stepping methods*/
	bool AStarSearch_Step(step_AStar& step, std::vector<std::vector<std::optional<Heuristic>>>& nodeWithHeuristic);
	void UniformSearch_Step(step_Uniform& step);
};

struct result
{
    std::vector<position> path;
    std::chrono::milliseconds duration;
    size_t expansion;
};

std::vector<std::vector<std::optional<Heuristic>>> makeNodesWithHeuristic(const std::vector<std::vector<std::optional<Node>>>& nodes);
std::vector<std::vector<std::optional<Cost>>> makeNodesWithCost(const std::vector<std::vector<std::optional<Node>>>& nodes);
#endif // SOLVER_H
