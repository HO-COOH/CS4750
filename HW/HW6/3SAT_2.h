#pragma once
#pragma once
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <optional>

struct variable
{
	size_t index;
	bool value;									//the value of the variable
	std::vector<bool> remain = { true,false };	//the remaining value of the variable {T,F}
	bool assigned = false;						//assigned?
	size_t degree = 0;
	std::vector<std::pair<size_t, short>> appearance;	//which clauses it is in and position(0,1,2)
	bool operator<(const variable& v2) const
	{
		return degree < v2.degree;
	}
};

struct SAT
{
	char count = 3;
	size_t vars[3];
	bool sign[3];			//positive or negative
};

class Three_SAT
{
	std::vector<SAT> constraints;
	std::vector<std::optional<variable>> assignment;
	std::priority_queue<variable> unassigned_var;
	variable PickVar();
	bool satisfied(size_t clause_index) const;
	bool _checking(size_t clause_index) const;
public:
	Three_SAT(const std::string& fileName);
	bool consistent(const variable& var) const;
	bool Recursive_Backtracking();
	void BacktrackingSearch();

	/*Forward_checking*/
	void Forward_Checking(variable& var);
	/*DEBUG*/
	void Verify() const;
};
