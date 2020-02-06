#pragma once
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <variant>

struct variable
{
	size_t index;
	bool value;									//the value of the variable
	std::vector<bool> remain = { true,false };	//the remaining value of the variable {T,F}
	bool assigned = false;						//assigned?
	size_t degree = 0;
	std::vector<std::pair<size_t, size_t>> appearance;	//which clauses it is in and position(0,1,2)
	bool operator<(const variable& v2) const
	{
		//if (remain.size() > v2.remain.size())
		//	return true;
		//else if (remain.size() < v2.remain.size())
		//	return false;
		//else
			return degree < v2.degree;
	}
};

struct SAT
{
	size_t count = 3;
	size_t vars[3];	
	bool sign[3];			//positive or negative
};

class Three_SAT
{
	std::vector<variable> variables;
	std::vector<SAT> constraints;
	
	std::list<size_t> assignment;
	std::list<size_t> unassigned;

	bool satisfied(size_t clause_index) const;	//Is the constraints[clause_index] satisfied? Used by IsConsistent()
public:
	Three_SAT(const std::string& fileName);	
	variable& PickVar();
	bool IsConsistent(variable& var, bool value);
	void AssignVar(variable& var, bool value);
	void UnassignVar(variable& var);
	
	
	bool _checking(size_t clause_index) const;

	size_t assignments;

	/*Forward_checking*/
	std::pair<std::vector<variable>, bool> Forward_Checking(variable& var);
	void Restore(std::vector<variable>& modified);
	/*DEBUG*/
	bool IsFinished() const;
	void PrintResult() const;
};


bool Recursive_Backtracking(Three_SAT& problem);
void BacktrackingSearch(Three_SAT& problem);