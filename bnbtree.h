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

#include "bnbtypes.h"
#include "subproblem.h"

#include <map>
#include <memory>
#include <limits>

namespace BnB
{
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
	void updateIncumbent(Subproblem* newIncumbent);
	bool gapClosed();

	double getLB();
	double getUB();

private:
	std::unique_ptr<SearchStrategy> mActive;
	unsigned int mNumExplored;

	Sense mSense;

	SubPtr mIncumbent;
	std::map<double,int> mBounds;
};

};

#endif // BNBTREE_H



