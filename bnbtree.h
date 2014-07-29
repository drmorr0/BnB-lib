#ifndef BNBTREE_H
#define BNBTREE_H
/*
 * bnbtree.h: (c) David R. Morrison, July 2014
 *
 * A class for maintaining a branch-and-bound search tree for an arbitrary optimization problem; the
 * class is extensible by providing custom lower bound functions, branching strategies, and search
 * strategies.  Extensions such as branch-and-price (B&P) and branch-and-cut (B&C) are also
 * supported.
 *
 */

#include "subproblem.h"

#include <memory>
#include <limits>

namespace BnB
{
typedef std::unique_ptr<Subproblem> SubPtr;
const double PosInf = std::numeric_limits<double>::infinity();
const double NegInf = -PosInf;

enum Sense { Minimization, Maximization };

class SearchStrategy
{
public:
	virtual ~SearchStrategy() = 0;

	virtual void push(SubPtr&& s) = 0;
	virtual SubPtr pop() = 0;
	virtual bool empty() const = 0;
};

class Tree
{
public:
	Tree(Subproblem* root, SearchStrategy* searcher, const Sense& sense);
	Subproblem* explore();
	void testIncumbent(Subproblem* newIncumbent);

private:
	std::unique_ptr<SearchStrategy> mActive;
	unsigned int mNumExplored;

	Sense mSense;
	double mLB;
	double mUB;

	SubPtr mIncumbent;
};

};

#endif // BNBTREE_H



