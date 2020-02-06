#include "3SAT_2.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stack>

using namespace std;

static size_t assignments = 0;


variable Three_SAT::PickVar()
{
	auto var = unassigned_var.top();
	unassigned_var.pop();
	return var;
}

bool Three_SAT::satisfied(size_t clause_index) const
{
	for (auto i = 0; i < constraints[clause_index].count; ++i)
	{
		const size_t& varindex = constraints[clause_index].vars[i];
		const bool& sign = constraints[clause_index].sign[i];
		if (!assignment[varindex].has_value())
			return true;
		if (assignment[varindex].value().value)	//var == T
		{
			if (sign)	//var == T && +var
				return true;
		}
		else			//var ==F
		{
			if (!sign)	//var ==F && -var
				return true;
		}
	}
	return false;
}

Three_SAT::Three_SAT(const std::string& fileName)
{
	assignments = 0;
	ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		cerr << "File is not opened successfully!\n";
		abort();
	}
	string meta;
	inFile >> meta >> meta;
	int variable_num;
	int clause_num;
	inFile >> variable_num >> clause_num;
	vector<variable> variables(variable_num);
	for (size_t i = 0; i < (size_t)variable_num; ++i)
		variables[i].index = i;
	constraints.reserve(clause_num);
	for (size_t i = 0; i < (size_t)clause_num; ++i)
	{
		int var;
		SAT temp;
		size_t j = 0;
		while (1)
		{
			inFile >> var;
			if (var == 0)
				break;
			temp.vars[j] = (var > 0) ? var - 1 : -var - 1;
			temp.sign[j] = (var > 0) ? true : false;
			++variables[temp.vars[j]].degree;
			variables[temp.vars[j]].appearance.push_back({ i,j });
			++j;
		}
		temp.count = j;
		constraints.push_back(temp);
	}
	assignment.resize(variable_num);
	for (auto& var : variables)
		unassigned_var.push(var);
}


bool Three_SAT::consistent(const variable& var) const
{
	for (const auto& clause : var.appearance)
	{
		if (!satisfied(clause.first))
			return false;
	}
	return true;
}


bool Three_SAT::Recursive_Backtracking()
{
	//if (unassigned_var.empty())
	//	return true;
	//auto var = PickVar();
	///*Assign values*/
	//for (const auto& value_assign : var.remain)
	//{
	//	var.value = value_assign;
	//	var.assigned = true;
	//	++assignments;
	//	if (consistent(var))
	//	{
	//		assignment.push_back(var.index);
	//		if (Recursive_Backtracking())
	//			return true;
	//		else	//result==fail
	//		{
	//			var.assigned = false;
	//			//unassigned_var.insert(current_pos, varIndex);
	//			assignment.pop_back();
	//		}
	//	}
	//	var.assigned = false;
	//}
	//return false;
	stack<variable> temp;
	while (!unassigned_var.empty())
	{
		auto var = PickVar();
		for (const auto& value : var.remain)
		{
			auto new_var(var);
			new_var.assigned = true;
			new_var.value = value;
			if (consistent(new_var))
				temp.push(new_var);
		}
	}
	return true;
}

void Three_SAT::BacktrackingSearch()
{
	if (!Recursive_Backtracking())
		cout << "No solution!\n";
	/*print result*/
	size_t i = 0;
	for (auto& var : assignment)
	{
		cout << "V" << i << "=" << ((var.value().value) ? "T " : "F ");
		if (i++ % 10 == 9)
			cout << '\n';
	}
	cout << "\nAssignment=" << assignments << '\n';
}

bool Three_SAT::_checking(size_t clause_index) const//return true if two variable is assigned and false
{
	//short count = 0;
	//auto& clause = constraints[clause_index];
	//for (auto i = 0; i < clause.count; ++i)
	//{
	//	if (variables[clause.vars[i]].value && variables[clause.vars[i]].assigned && !clause.sign[i])	//var: -T
	//		++count;
	//	else
	//	{
	//		if (!variables[clause.vars[i]].value && variables[clause.vars[i]].assigned && clause.sign[i])	//var: +F
	//			++count;
	//	}
	//}
	//if (count >= clause.count - 1)
	//{

	//}
	return true;
}

void Three_SAT::Forward_Checking(variable& var)
{
	for (auto& clauseIndex : var.appearance)
	{
		if (var.value && constraints[clauseIndex.first].sign[clauseIndex.second])//var==T
		{
			//if(constraints[clauseIndex].)
		}
	}
}

void Three_SAT::Verify() const
{
	//for (size_t clause_index = 0; clause_index < constraints.size(); ++clause_index)
	//{
	//	bool satisfy = false;
	//	for (auto i = 0; i < constraints[clause_index].count; ++i)
	//	{
	//		const size_t& varindex = constraints[clause_index].vars[i];
	//		const bool& sign = constraints[clause_index].sign[i];
	//		if (!variables[varindex].assigned)
	//			cerr << "Error! Variable" << varindex << " not assigned!\n";
	//		if (variables[varindex].value)	//var == T
	//		{
	//			if (sign)	//var == T && +var
	//			{
	//				satisfy = true;
	//				break;
	//			}
	//		}
	//		else			//var ==F
	//		{
	//			if (!sign)	//var ==F && -var
	//			{
	//				satisfy = true;
	//				break;
	//			}
	//		}
	//	}
	//	if (!satisfy)
	//		cerr << "Error! Not sastifying " << clause_index << " clause!\n";
	//}
}
