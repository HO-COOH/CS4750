#include "solver.h"
#include <iostream>
#include <queue>

using namespace std;

enum class direction{UP, DOWN, LEFT, RIGHT};

bool Solver::isNode(size_t _row, size_t _col) const
{
    if(!maze->maze[_row][_col])
        return false;
    //current is T
    if(left(_row, _col))    //T T ?
    {
        if(right(_row, _col))   //T T T
        {                                            //  T
             if(down(_row, _col) || up(_row, _col))  //T T T    or  T T T
                return true;                        //                T
        }
        else    //T T F
            return true;
    }
    else    //F T ?
    {
        if(right(_row, _col))   //F T T
            return true;
        else    //F T F
        {
            if(!down(_row, _col) || !up(_row, _col))
                return true;
        }
    }
    return  false;
}

//size_t Solver::makeNodes()
//{
//    //make a top nodes buffer
//    vector<optional<pair<size_t, size_t>>> topNodes(maze->cols);
//    //make start node
//    nodes.resize(maze->rows);
//    for(auto& each_row:nodes)
//        each_row.resize(maze->cols);
//        //nodes.emplace_back(Node{{1,1},{}, {}, {},{}});
//    nodes[1][1]=Node{{1,1},{},{},{},{},{}};
//        //topNodes[1]=nodes.back()._position;
//    topNodes[1]={1,1};
//    //start from row 2 -> row maze.size()-3 (start node: [1,1]  end node: [maze.size-2, maze[0].size-2]
//    //start from row 2 ->
//    for(size_t row=1; row< maze->rows-1; ++row)
//    {
//        //from col 1 -> col maze[0].size()-2
//        optional<pair<size_t, size_t>> leftNeighbor;
//        for(size_t col=1; col<maze->cols-1; ++col)
//        {
//            if(isNode(row, col))
//            {
//                /*Debug*/
//				//cout << "(" << row << "," << col << ") is node.\n";
//				//connect the left neighbor
//                Node current=Node{{row, col},{},{},{},{},{}};
//                if(leftNeighbor)
//                {
//                    nodes[row][leftNeighbor->second]->rightNeighbor={row,col};
//                    current.leftNeighbor=leftNeighbor.value();
//                }
//                //if clear above, connect to the node above
//				if (up(row, col) && topNodes[col].has_value())
//				{
//					current.upNeighbor = topNodes[col].value();
//					nodes[topNodes[col].value().first][topNodes[col].value().second]->downNeighbor = { row, col };
//				}
//                //if clear down, make current node as the new topNode
//                if(down(row,col))
//                    topNodes[col]={row, col};
//                nodes[row][col]=current;

//                //change the leftNeighbor to current
//                leftNeighbor={row, col};
//            }
//        }
//    }
//    nodesMade=true;
//    return nodes.size();
//}

void Solver::makeNodes()
{
    auto createNode=[&](size_t row, size_t col){ nodes[row][col]=Node{{row, col}, {}, {}, {}, {}, {}};};
    /*init top nodes*/
    vector<optional<pair<size_t, size_t>>> topNodes(maze->cols);
    /*make start node*/
    nodes.resize(maze->rows);
    for(auto& each_row:nodes)
        each_row.resize(maze->cols);
    nodes[1][1]=Node{{1,1},{},{},{},{},{}};
    topNodes[1]={1,1};
    for(size_t row=1; row< maze->rows-1; ++row)
    {
        optional<pair<size_t, size_t>> leftNeighbor;
        for(size_t col=1; col<maze->cols-1; ++col)
        {
            bool current=false;
            if(!maze->maze[row][col])
                continue;
            if(maze->maze[row][col-1])    //T T ?
            {
                if(maze->maze[row][col+1])  //T T T  create node only if clear above or below
                {
                    if(maze->maze[row-1][col] || maze->maze[row+1][col])
                    {
                        createNode(row, col);
                        current=true;
                        if(leftNeighbor.has_value())
                        {
                            nodes[leftNeighbor->first][leftNeighbor->second]->rightNeighbor={row, col};
                            nodes[row][col]->leftNeighbor=leftNeighbor.value();
                        }
                        leftNeighbor={row, col};
                        current=true;
                    }
                }
                else    //T T F
                {
                    createNode(row, col);
                    current=true;
                    if(leftNeighbor.has_value())
                    {
                        nodes[leftNeighbor->first][leftNeighbor->second]->rightNeighbor={row, col};
                        nodes[row][col]->leftNeighbor=leftNeighbor.value();
                        leftNeighbor.reset();
                    }
                }

            }
            else    //F T ?
            {
                if(maze->maze[row][col+1])  //F T T
                {
                    createNode(row, col);
                    current=true;
                    leftNeighbor={row, col};
                }
                else    //F T F create node only if above or under is wall
                {
                    if(maze->maze[row-1][col] || maze->maze[row+1][col])
                    {
                        current=true;
                        createNode(row, col);
                    }
                }
            }
            if(current) //node is created
            {
                if(maze->maze[row-1][col])   //if clear above, connect the upNeighbor of current
                {
                    nodes[topNodes[col]->first][topNodes[col]->second]->downNeighbor={row, col};
                    nodes[row][col]->upNeighbor=topNodes[col];
                }
                if(maze->maze[row+1][col])   //if clear below, make current node as the new topNodes for connection
                    topNodes[col]={row, col};
                else
                    topNodes[col].reset();
            }
        }
    }
	nodesMade = true;
}


size_t Solver::ExpandNodes(queue<Node>& fringe, const Node& nodeToExpand, const vector<vector<bool>>& visited)
{
	size_t expansion = 0;
    if(nodeToExpand.upNeighbor && !visited[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second])
    {
        Node temp=nodes[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second].value();
        temp.path=nodeToExpand.path;
        temp.path.push_back(nodeToExpand._position);
        fringe.push(temp);
		++expansion;
    }
    if(nodeToExpand.downNeighbor && !visited[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second])
    {
        Node temp=nodes[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second].value();
        temp.path=nodeToExpand.path;
        temp.path.push_back(nodeToExpand._position);
        fringe.push(temp);
		++expansion;
    }
    if(nodeToExpand.leftNeighbor && !visited[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second])
    {
       Node temp=nodes[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second].value();
       temp.path=nodeToExpand.path;
       temp.path.push_back(nodeToExpand._position);
       fringe.push(temp);
	   ++expansion;
    }
    if(nodeToExpand.rightNeighbor && !visited[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second])
    {
        Node temp=nodes[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second].value();
        temp.path=nodeToExpand.path;
        temp.path.push_back(nodeToExpand._position);
        fringe.push(temp);
		++expansion;
    }
	return expansion;
}

size_t Solver::ExpandNodes(std::stack<Node>&fringe, const Node& nodeToExpand, const std::vector<std::vector<bool>>& visited)
{
    size_t expansion = 0;
    if(nodeToExpand.upNeighbor && !visited[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second])
    {
        Node temp=nodes[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second].value();
        temp.path=nodeToExpand.path;
        temp.path.push_back(nodeToExpand._position);
        fringe.push(temp);
        ++expansion;
    }
    if(nodeToExpand.downNeighbor && !visited[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second])
    {
        Node temp=nodes[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second].value();
        temp.path=nodeToExpand.path;
        temp.path.push_back(nodeToExpand._position);
        fringe.push(temp);
        ++expansion;
    }
    if(nodeToExpand.leftNeighbor && !visited[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second])
    {
       Node temp=nodes[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second].value();
       temp.path=nodeToExpand.path;
       temp.path.push_back(nodeToExpand._position);
       fringe.push(temp);
       ++expansion;
    }
    if(nodeToExpand.rightNeighbor && !visited[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second])
    {
        Node temp=nodes[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second].value();
        temp.path=nodeToExpand.path;
        temp.path.push_back(nodeToExpand._position);
        fringe.push(temp);
        ++expansion;
    }
    return expansion;
}

result Solver::BreadthFirstSearch()
{
    Timer t;
    if(!nodesMade)
        makeNodes();
	size_t expansion = 0;
    //init a map with the same size as the maze
    vector<vector<bool>> visited(maze->rows);
    for(auto& each_row:visited)
    {
        each_row.resize(maze->cols);
        fill(each_row.begin(), each_row.end(), false);
    }

    queue<Node> fringe;
    fringe.push(nodes[1][1].value());
    while(!fringe.empty())
    {
        const Node current=fringe.front();
        visited[current._position.first][current._position.second]=true;    //?
        if(current==nodes[maze->rows-2][maze->cols-2].value())   //found!
        {
            return { current.path, t.duration(), expansion };
        }
        fringe.pop();
		visited[current._position.first][current._position.second] = true;
        expansion+=ExpandNodes(fringe, current, visited);
    }
    //not found
    return { {}, t.duration(),expansion };
}

result Solver::DepthFirstSearch()
{
    Timer t;
    if(!nodesMade)
        makeNodes();
    size_t expansion=0;
    //init a map with the same size as the maze
    vector<vector<bool>> visited(maze->rows);
    for(auto& each_row:visited)
    {
        each_row.resize(maze->cols);
        fill(each_row.begin(), each_row.end(), false);
    }

    stack<Node> fringe;
    fringe.push(nodes[1][1].value());
    while(!fringe.empty())
    {
        const Node current=fringe.top();
        visited[current._position.first][current._position.second]=true;
        if(current==nodes[maze->rows-2][maze->cols-2].value())   //found!
        {
            return { current.path, t.duration(), expansion };
        }
        fringe.pop();
        expansion+=ExpandNodes(fringe, current, visited);
    }
    //not found
    return { {}, t.duration(),expansion };
}


vector<vector<optional<Heuristic>>> makeNodesWithHeuristic(const vector<vector<optional<Node>>>& nodes)
{
    vector<vector<optional<Heuristic>>> heuristics(nodes.size());
    size_t rows=nodes.size();
    size_t cols=nodes.front().size();
    for(size_t row=0; row<rows; ++row)
    {
        heuristics[row].resize(cols);
        for(size_t col=0; col<cols; ++col)
        {
            if(nodes[row][col].has_value()) //copy the info of the neighbors
            {
                Heuristic current{nodes[row][col].value()};
                if(nodes[row][col]->upNeighbor.has_value())
                    current.upCost=(nodes[row][col]->_position.first-nodes[row][col]->upNeighbor->first);
                if(nodes[row][col]->downNeighbor.has_value())
                    current.downCost=(nodes[row][col]->downNeighbor->first-nodes[row][col]->_position.first);
                if(nodes[row][col]->leftNeighbor.has_value())
                    current.leftCost=(nodes[row][col]->_position.second-nodes[row][col]->leftNeighbor->second);
                if(nodes[row][col]->rightNeighbor.has_value())
                    current.rightCost=(nodes[row][col]->rightNeighbor->second-nodes[row][col]->_position.second);
                current.heuristic=rows-2-current._position.first+cols-2-current._position.second;
                heuristics[row][col]=current;
            }
        }
    }
    return heuristics;
}

size_t ExpandNodes(priority_queue<Heuristic>& fringe, Heuristic& nodeToExpand, const vector<vector<bool>>& visited, vector<vector<optional<Heuristic>>>& nodes)
{
    size_t expansion=0;
    if(nodeToExpand.upNeighbor && !visited[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second])
    {
        Heuristic temp=nodes[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second].value();
		temp.from = nodeToExpand._position;
        temp.cost+=nodeToExpand.upCost.value();
        temp.heuristic+=nodeToExpand.upCost.value();
        fringe.push(temp);
        ++expansion;
    }
    if(nodeToExpand.downNeighbor && !visited[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second])
    {
        Heuristic temp=nodes[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second].value();
		temp.from = nodeToExpand._position;
        temp.cost+=nodeToExpand.downCost.value();
        temp.heuristic+=nodeToExpand.downCost.value();
        fringe.push(temp);
        ++expansion;
    }
    if(nodeToExpand.leftNeighbor && !visited[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second])
    {
       Heuristic temp=nodes[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second].value();
	   temp.from = nodeToExpand._position;
       temp.cost+=nodeToExpand.leftCost.value();
       temp.heuristic+=nodeToExpand.leftCost.value();
       fringe.push(temp);
       ++expansion;
    }
    if(nodeToExpand.rightNeighbor && !visited[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second])
    {
        Heuristic temp=nodes[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second].value();
		temp.from = nodeToExpand._position;
        temp.cost+=nodeToExpand.rightCost.value();
        temp.heuristic+=nodeToExpand.rightCost.value();
        fringe.push(temp);
        ++expansion;
    }
	return expansion;
}

result Solver::AStarSearch()
{
    Timer t;
    if(!nodesMade)
        makeNodes();
    auto heuristics=makeNodesWithHeuristic(nodes);

    size_t expansion=0;
    vector<vector<bool>> visited(maze->rows);
    for(auto& each_row:visited)
    {
        each_row.resize(maze->cols);
        fill(each_row.begin(), each_row.end(), false);
    }

    priority_queue<Heuristic> nodeWithHeuristic;
    nodeWithHeuristic.push(heuristics[1][1].value());
	stack<Heuristic> finished;
    while(!nodeWithHeuristic.empty())
    {
        Heuristic current=nodeWithHeuristic.top();
		if (current == heuristics[maze->rows - 2][maze->cols - 2])
		{
			vector<position> path;
			Heuristic pre = current;
			while (!finished.empty())
			{
				if (pre.from.first == finished.top()._position.first && pre.from.second == finished.top()._position.second)
				{
					path.push_back(pre._position);
					pre = finished.top();
				}
				finished.pop();
			}
			return { path, t.duration(), expansion };
		}
        visited[current._position.first][current._position.second]=true;
		finished.push(current);
		nodeWithHeuristic.pop();
        expansion+=::ExpandNodes(nodeWithHeuristic, current, visited, heuristics);
    }
    return {{}, t.duration(), expansion};
}

vector<vector<optional<Cost>>> makeNodesWithCost(const vector<vector<optional<Node>>>& nodes)
{
    vector<vector<optional<Cost>>> costs(nodes.size());
    for(size_t row=0; row<nodes.size(); ++row)
    {
        costs[row].resize(nodes.front().size());
        for(size_t col=0; col<nodes.front().size(); ++col)
        {
            if(nodes[row][col].has_value()) //copy the info of the neighbors
            {
                //*costs[row][col] = *nodes[row][col];
				costs[row][col].operator=(Cost{});
				costs[row][col].operator->()->operator=(nodes[row][col].value());
				costs[row][col]->_position = nodes[row][col]->_position;
                if(nodes[row][col]->upNeighbor.has_value())
                    costs[row][col]->upCost=(nodes[row][col]->_position.first-nodes[row][col]->upNeighbor->first);
                if(nodes[row][col]->downNeighbor.has_value())
                    costs[row][col]->downCost=(nodes[row][col]->downNeighbor->first-nodes[row][col]->_position.first);
                if(nodes[row][col]->leftNeighbor.has_value())
                    costs[row][col]->leftCost=(nodes[row][col]->_position.second-nodes[row][col]->leftNeighbor->second);
                if(nodes[row][col]->rightNeighbor.has_value())
                    costs[row][col]->rightCost=(nodes[row][col]->rightNeighbor->second-nodes[row][col]->_position.second);
            }
        }
    }
    return costs;
}
//

/*/////////////////////////////////*/
size_t ExpandNodes2(std::priority_queue<Cost>& fringe, const Cost& nodeToExpand, const std::vector<std::vector<bool>>& visited, const std::vector<std::vector<std::optional<Cost>>>& nodes)
{
	size_t expansion = 0;
	if (nodeToExpand.upNeighbor && !visited[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second])
	{
		Cost temp = nodes[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second].value();
		temp.from = nodeToExpand._position;
		temp.cost += nodeToExpand.upCost.value();
		fringe.push(temp);
		++expansion;
	}
	if (nodeToExpand.downNeighbor && !visited[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second])
	{
		Cost temp = nodes[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second].value();
		temp.from = nodeToExpand._position;
		temp.cost += nodeToExpand.downCost.value();
		fringe.push(temp);
		++expansion;
	}
	if (nodeToExpand.leftNeighbor && !visited[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second])
	{
		Cost temp = nodes[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second].value();
		temp.from = nodeToExpand._position;
		temp.cost += nodeToExpand.leftCost.value();
		fringe.push(temp);
		++expansion;
	}
	if (nodeToExpand.rightNeighbor && !visited[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second])
	{
		Cost temp = nodes[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second].value();
		temp.from = nodeToExpand._position;
		temp.cost += nodeToExpand.rightCost.value();
		fringe.push(temp);
		++expansion;
	}
	return expansion;
}

result Solver::UniformSearch()
{
	Timer t;
	if (!nodesMade)
		makeNodes();
	auto costs = makeNodesWithCost(nodes);
	size_t expansion = 0;
	vector<vector<bool>> visited(maze->rows);
	for (auto& each_row : visited)
	{
		each_row.resize(maze->cols);
		fill(each_row.begin(), each_row.end(), false);
	}
	stack<Cost> finished;
	priority_queue<Cost> nodeWithCost;
	nodeWithCost.push(costs[1][1].value());
	while (!nodeWithCost.empty())
	{
		Cost current = nodeWithCost.top();
		if (current == costs[maze->rows - 2][maze->cols - 2])
		{
			vector<position> path;
			Cost pre = current;
			while (!finished.empty())
			{
				if (pre.from.first == finished.top()._position.first && pre.from.second == finished.top()._position.second)
				{
					path.push_back(pre._position);
					pre = finished.top();
				}
				finished.pop();
			}
			return { path, t.duration(), expansion };
		}
		visited[current._position.first][current._position.second] = true;
		finished.push(current);
		nodeWithCost.pop();
		expansion += ::ExpandNodes2(nodeWithCost, current, visited, costs);
	}
	return { {}, t.duration(), expansion };
}

/*Stepping search methods*/
bool Solver::AStarSearch_Step(step_AStar& step, vector<vector<optional<Heuristic>>>& nodesWithHeuristic)
{
	if (!nodesMade)
		makeNodes();
	if (!step.fringe.empty())
	{
		auto current = step.fringe.top();
		if (current.operator== (nodesWithHeuristic[maze->rows - 2][maze->cols - 2].value()))
			return true;
		step.fringe.pop();
		step.visited[current._position.first][current._position.second] = true;
		::ExpandNodes(step.fringe, current, step.visited, nodesWithHeuristic);
	}
	else
	{
		step.fringe.push(nodesWithHeuristic[1][1].value());
	}
	return false;
}

void Solver::UniformSearch_Step(step_Uniform& step)
{
	
}



/*old implementation, inefficent in copy the path*/

//size_t ExpandNodes(priority_queue<Heuristic>& fringe, Heuristic& nodeToExpand, const vector<vector<bool>>& visited, vector<vector<optional<Heuristic>>>& nodes)
//{
//	size_t expansion = 0;
//	if (nodeToExpand.upNeighbor && !visited[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second])
//	{
//		Heuristic temp = nodes[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second].value();
//		temp.path = nodeToExpand.path;
//		temp.path.push_back(nodeToExpand._position);
//		temp.cost += nodeToExpand.upCost.value();
//		temp.heuristic += nodeToExpand.upCost.value();
//		fringe.push(temp);
//		++expansion;
//	}
//	if (nodeToExpand.downNeighbor && !visited[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second])
//	{
//		Heuristic temp = nodes[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second].value();
//		temp.path = nodeToExpand.path;
//		temp.path.push_back(nodeToExpand._position);
//		temp.cost += nodeToExpand.downCost.value();
//		temp.heuristic += nodeToExpand.downCost.value();
//		fringe.push(temp);
//		++expansion;
//	}
//	if (nodeToExpand.leftNeighbor && !visited[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second])
//	{
//		Heuristic temp = nodes[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second].value();
//		temp.path = nodeToExpand.path;
//		temp.path.push_back(nodeToExpand._position);
//		temp.cost += nodeToExpand.leftCost.value();
//		temp.heuristic += nodeToExpand.leftCost.value();
//		fringe.push(temp);
//		++expansion;
//	}
//	if (nodeToExpand.rightNeighbor && !visited[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second])
//	{
//		Heuristic temp = nodes[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second].value();
//		temp.path = nodeToExpand.path;
//		temp.path.push_back(nodeToExpand._position);
//		temp.cost += nodeToExpand.rightCost.value();
//		temp.heuristic += nodeToExpand.rightCost.value();
//		fringe.push(temp);
//		++expansion;
//	}
//	return expansion;
//}

//size_t ExpandNodes(std::priority_queue<Cost>&fringe, const Cost& nodeToExpand, const std::vector<std::vector<bool>>& visited, const std::vector<std::vector<std::optional<Cost>>>& nodes)
//{
//    size_t expansion = 0;
//    if(nodeToExpand.upNeighbor && !visited[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second])
//    {
//        Cost temp=nodes[nodeToExpand.upNeighbor.value().first][nodeToExpand.upNeighbor.value().second].value();
//        temp.path=nodeToExpand.path;
//        temp.path.push_back(nodeToExpand._position);
//        temp.cost+=nodeToExpand.upCost.value();
//        fringe.push(temp);
//        ++expansion;
//    }
//    if(nodeToExpand.downNeighbor && !visited[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second])
//    {
//        Cost temp=nodes[nodeToExpand.downNeighbor.value().first][nodeToExpand.downNeighbor.value().second].value();
//        temp.path=nodeToExpand.path;
//        temp.path.push_back(nodeToExpand._position);
//        temp.cost+=nodeToExpand.downCost.value();
//        fringe.push(temp);
//        ++expansion;
//    }
//    if(nodeToExpand.leftNeighbor && !visited[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second])
//    {
//       Cost temp=nodes[nodeToExpand.leftNeighbor.value().first][nodeToExpand.leftNeighbor.value().second].value();
//       temp.path=nodeToExpand.path;
//       temp.path.push_back(nodeToExpand._position);
//       temp.cost+=nodeToExpand.leftCost.value();
//       fringe.push(temp);
//       ++expansion;
//    }
//    if(nodeToExpand.rightNeighbor && !visited[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second])
//    {
//        Cost temp=nodes[nodeToExpand.rightNeighbor.value().first][nodeToExpand.rightNeighbor.value().second].value();
//        temp.path=nodeToExpand.path;
//        temp.path.push_back(nodeToExpand._position);
//        temp.cost+=nodeToExpand.rightCost.value();
//        fringe.push(temp);
//        ++expansion;
//    }
//    return expansion;
//}
//
//result Solver::UniformSearch()
//{
//    Timer t;
//    if(!nodesMade)
//        makeNodes();
//    auto costs=makeNodesWithCost(nodes);
//    size_t expansion=0;
//    vector<vector<bool>> visited(maze->rows);
//    for(auto& each_row:visited)
//    {
//        each_row.resize(maze->cols);
//        fill(each_row.begin(), each_row.end(), false);
//    }
//
//    priority_queue<Cost> nodeWithCost;
//    nodeWithCost.push(costs[1][1].value());
//    while(!nodeWithCost.empty())
//    {
//        Cost current=nodeWithCost.top();
//        if(current==costs[maze->rows-2][maze->cols-2])
//            return {current.path, t.duration(), expansion};
//        visited[current._position.first][current._position.second]=true;
//        nodeWithCost.pop();
//        expansion+=::ExpandNodes(nodeWithCost, current, visited, costs);
//
//    }
//
//
//    return {{}, t.duration(), expansion};
//}