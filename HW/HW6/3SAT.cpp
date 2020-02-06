#include "3SAT.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stack>

using namespace std;

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
	variables.resize(variable_num);
	for (size_t i = 0; i < (size_t)variable_num; ++i)
		variables[i].index = i;
	constraints.reserve(clause_num);
	for (size_t i=0; i<(size_t)clause_num; ++i)
	{
		int var;
		SAT temp;
		size_t j = 0;
		while(1)
		{
			inFile >> var;
			if (var == 0)
				break;
			temp.vars[j]=(var > 0) ? var - 1 : -var - 1;
			temp.sign[j] = (var > 0) ? true : false;
			++variables[temp.vars[j]].degree;
			variables[temp.vars[j]].appearance.push_back({ i,j });
			++j;
		}
		temp.count = j;
		constraints.push_back(temp);
	}
	for (size_t i = 0; i < (size_t)variable_num; ++i)
		unassigned.push_back(i);
	cout << "Finished init! Variables=" << variables.size() << " Clauses=" << constraints.size() << "\n";
}


variable& Three_SAT::PickVar()
{
	if (unassigned.empty())
		cout << "Error! There are no unassigned var!\n";
	size_t current = unassigned.front();
	for (auto varIndex : unassigned)
	{
		if (variables[varIndex].degree > variables[current].degree)
			current = varIndex;
	}
	return variables[current];
}

bool Three_SAT::satisfied(size_t clause_index) const
{
	for (size_t i=0; i<constraints[clause_index].count; ++i)
	{
		const size_t& varindex = constraints[clause_index].vars[i];
		const bool& sign = constraints[clause_index].sign[i];
		if (!variables[varindex].assigned)
			return true;
		if (variables[varindex].value)	//var == T
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

bool Three_SAT::IsConsistent(variable& var, bool value)
{
	if (var.assigned)
		cout << "Already assigned!\n";
	var.assigned = true;
	var.value = value;
	for (auto& loc : var.appearance)
	{
		if (!satisfied(loc.first))
		{
			var.assigned = false;
			return false;
		}
	}
	var.assigned = false;
	return true;
}

void Three_SAT::AssignVar(variable& var, bool value)
{
	var.assigned = true;
	var.value = value;
	++assignments;
	assignment.push_back(var.index);
	unassigned.remove(var.index);
}

void Three_SAT::UnassignVar(variable& var)
{
	var.assigned = false;
	assignment.remove(var.index);
	unassigned.push_back(var.index);
}

bool Three_SAT::_checking(size_t clause_index) const
{
	return false;
}


bool Recursive_Backtracking(Three_SAT& problem)
{
	if (problem.IsFinished())
		return true;
	auto& var = problem.PickVar();
	if (problem.assignments <= 8)
		cout <<"assignment"<<problem.assignments <<" V"<<var.index << '\n';
	/*Assign values*/
	for (const auto& value_assign: var.remain)
	{
		if (problem.IsConsistent(var,value_assign))
		{
			problem.AssignVar(var, value_assign);
			auto result=problem.Forward_Checking(var);
			if (result.second)
			{
				if (Recursive_Backtracking(problem))
					return true;
				else	//result==fail
				{
					problem.UnassignVar(var);
					problem.Restore(result.first);
					continue;
				}
			}
			else
				problem.UnassignVar(var);
		}
	}
	return false;
}

void BacktrackingSearch(Three_SAT& problem)
{
	if (!Recursive_Backtracking(problem))
		;
		//cout<<"No solution!\n";
	problem.PrintResult();
	cout << "\nAssignment=" << problem.assignments << '\n';
}

//bool Three_SAT::_checking(size_t clause_index) const//return true if two variable is assigned and false
//{
//	short count = 0;
//	auto& clause = constraints[clause_index];
//	for (size_t i = 0; i < clause.count; ++i)
//	{
//		if (variables[clause.vars[i]].value &&variables[clause.vars[i]].assigned && !clause.sign[i])	//var: -T
//			++count;
//		else
//		{
//			if (!variables[clause.vars[i]].value && variables[clause.vars[i]].assigned && clause.sign[i])	//var: +F
//				++count;
//		}
//	}
//	if (count >= clause.count - 1)
//	{
//
//	}
//	return true;
//}

std::pair<std::vector<variable>, bool> Three_SAT::Forward_Checking(variable& var)
{
	vector<variable> modified;
	for (auto& clauseIndex : var.appearance)
	{
		auto& clause = constraints[clauseIndex.first];
		size_t false_count = 0;
		size_t pos=10;
		bool flag = false;
		for (size_t i = 0; i < clause.count; ++i)
		{
			variable& var = variables[clause.vars[i]];
			if (!var.assigned)
			{
				pos = i;
				flag = true;
				continue;
			}
			if ((var.value && !clause.sign[i]) || (!var.value && clause.sign[i]))//var==-T || var==F
				++false_count;
		}
		if (false_count == clause.count)
		{
			//cout << "Error! This clause" << clauseIndex.first << " is not satisfied in forward checking!\n";
			return { {},false };
		}
		if (false_count == clause.count - 1&&flag)	//one var can reduce its domain
		{
			modified.push_back(variables[clause.vars[pos]]);
			auto& varToAssign = variables[clause.vars[pos]];
			bool valueToAssign = clause.sign[pos] ? true : false;
			//if (!IsConsistent(varToAssign, valueToAssign))
			//	return { {}, false };
			AssignVar(varToAssign, valueToAssign);
		}
	}
	return { modified, true };
}

void Three_SAT::Restore(vector<variable>& modified)
{
	for (auto& var : modified)
	{
		var.assigned = false;
		variables[var.index] = var;
		unassigned.push_back(var.index);
		assignment.remove(var.index);
	}
}

bool Three_SAT::IsFinished() const
{
	return unassigned.empty();
}

void Three_SAT::PrintResult() const
{
	size_t i = 0;
	for (const auto& var : variables)
	{
		cout << "V" << var.index << "=" << ((var.value) ? "T " : "F ");
		if (i++ % 10 == 9)
			cout << '\n';
	}
}
