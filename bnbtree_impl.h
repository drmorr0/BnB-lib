// bnbtree.cpp: (c) David R. Morrison, July 2014
// Implementation details for the branch-and-bound tree class

#include <cstdio>
#include <algorithm>

namespace BnB
{

template <class SearchContainerT>
Tree<SearchContainerT>::Tree(const Subproblem& root)
{
	mActive.push(root);
}

template <class SearchContainerT>
Subproblem Tree<SearchContainerT>::explore()
{
	while (!mActive.empty())
	{
		Subproblem next = mActive.pop();

		// 1. Check to see if the subproblem can be pruned
		// 2. Check to see if the subproblem is terminal (and update incumbent)
		// 3. Generate children if neither 1 or 2

		auto children = next.getChildren();
		for_each(children.begin(), children.end(), 
				[&] (const Subproblem& child) { mActive.push(child); });
		++mNumExplored;
		printf("Explored %d subproblems\n", mNumExplored);
	}

	return Subproblem();
}

};


