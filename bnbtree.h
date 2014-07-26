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

namespace BnB
{

class SearchContainer
{
public:
	virtual void push(const Subproblem& s) = 0;
	virtual Subproblem pop() = 0;
	virtual bool empty() = 0;
};

class Tree
{
public:
	Tree(const Subproblem& root, SearchContainer* searcher);
	Subproblem explore();

private:
	std::unique_ptr<SearchContainer> mActive;
	Subproblem mIncumb;
	int mNumExplored;
	int mNumGenerated;
};

};

#endif // BNBTREE_H



