#ifndef SIMPLE_SUBPROBLEMS_H
#define SIMPLE_SUBPROBLEMS_H
/*
 * simple_subproblems.h: (c) David R. Morrison, July 2014
 *
 * A simple branch-and-bound tree for testing purposes
 */

#include "cbfs.h"
#include <cstdio>
#include <vector>

using namespace std;

class SimpleSubproblem : public BnB::CbfsSubproblem
{
public:
	SimpleSubproblem(unsigned int id = 0) : mId(id), mDepth(0), mNumPosAssgn(0) { }
	BnB::Subproblem* clone() const { return new SimpleSubproblem(*this); }
	vector<BnB::Subproblem*> children()
	{
		vector<BnB::Subproblem*> c;
		if (mId > 6) return c;

		SimpleSubproblem* left = new SimpleSubproblem(*this);
		SimpleSubproblem* right = new SimpleSubproblem(*this);
		left->mId = 2 * mId + 1; right->mId = 2 * mId + 2;
		++(left->mDepth); ++(left->mNumPosAssgn); ++(right->mDepth);
		c.push_back(left); c.push_back(right);
		return c;
	}

	double objValue() { return objValueVec[mId]; }
	double bound() { return boundsVec[mId]; }
	double mu() { return boundsVec[mId]; }
//	long contour() { return mDepth; }
//	long contour() { return mNumPosAssgn; }
	long contour() { return mId; }
	bool isTerminal() { return (mId > 6); }

private:
	size_t mId;
	size_t mDepth;
	size_t mNumPosAssgn;
	static const vector<double> objValueVec;
	static const vector<double> boundsVec;

private:
	void print() { printf("subproblem id %lu, mu = %0.2f, k = %ld", mId, mu(), contour()); }
};


#endif // SIMPLE_SUBPROBLEMS_H


