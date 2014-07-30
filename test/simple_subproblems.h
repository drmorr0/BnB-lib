#ifndef SIMPLE_SUBPROBLEMS_H
#define SIMPLE_SUBPROBLEMS_H
/*
 * simple_subproblems.h: (c) David R. Morrison, July 2014
 *
 * A simple branch-and-bound tree for testing purposes
 */

#include "subproblem.h"
#include <cstdio>
#include <vector>

using namespace std;

class SimpleSubproblem : public BnB::Subproblem
{
public:
	SimpleSubproblem(unsigned int id = 0) : mId(id) { }
	BnB::Subproblem* clone() const { return new SimpleSubproblem(*this); }
	vector<BnB::Subproblem*> children()
	{
		vector<BnB::Subproblem*> c;
		if (mId > 6) return c;

		c.push_back(new SimpleSubproblem(2 * mId + 1));
		c.push_back(new SimpleSubproblem(2 * mId + 2));
		return c;
	}

	double objValue() { return objValueVec[mId]; }
	double bound() { return boundsVec[mId]; }
	bool isTerminal() { return (mId > 6); }

private:
	size_t mId;
	static const vector<double> objValueVec;
	static const vector<double> boundsVec;

private:
	void print() { printf("subproblem id %lu", mId); }
};


#endif // SIMPLE_SUBPROBLEMS_H


