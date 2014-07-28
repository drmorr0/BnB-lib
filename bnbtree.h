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

typedef std::unique_ptr<Subproblem> SubPtr;

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
	Tree(const Subproblem& root, SearchStrategy* searcher);
	Subproblem* explore();

private:
	std::unique_ptr<SearchStrategy> mActive;
	unsigned int mNumExplored;
};

};

#endif // BNBTREE_H



