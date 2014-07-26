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

namespace BnB
{

template <class SearchContainerT>
class Tree
{
public:
	Tree(const Subproblem& root);
	Subproblem explore();

private:
	SearchContainerT mActive;	
	Subproblem mIncumb;
	int mNumExplored;
	int mNumGenerated;
};

};

#include "bnbtree_impl.h"

#endif // BNBTREE_H



