// bnbtree.cpp: (c) David R. Morrison, July 2014
// Implementation details for the branch-and-bound tree class

#include "bnbtree.h"

#include <cstdio>
#include <algorithm>

namespace BnB
{

Tree::Tree(const Subproblem& root, SearchContainer* searcher) :
	mActive(searcher)
{
	mActive->push(root);
}

Subproblem Tree::explore()
{
	while (!mActive->empty())
	{
		Subproblem next = mActive->pop();

		// 1. Check to see if the subproblem can be pruned
		// 2. Check to see if the subproblem is terminal (and update incumbent)
		// 3. Generate children if neither 1 or 2

		auto children = next.children();
		for_each(children.begin(), children.end(), 
				[&] (const Subproblem& child) { mActive->push(child); });
		++mNumExplored;
		printf("Explored %d subproblems\n", mNumExplored);
	}

	return Subproblem();
}

};


