// bnbtree.cpp: (c) David R. Morrison, July 2014
// Implementation details for the branch-and-bound tree class

#include "bnbtree.h"

#include <cstdio>
#include <algorithm>

using namespace std;

namespace BnB
{

SearchStrategy::~SearchStrategy() { }

Tree::Tree(Subproblem* root, SearchStrategy* searcher, const Sense& sense) :
	mActive(searcher),
	mNumExplored(0),
	mSense(sense),
	mLB(NegInf),
	mUB(PosInf),
	mIncumbent(nullptr)
{
	mActive->push(SubPtr(root));
}

Subproblem* Tree::explore()
{
	while (!mActive->empty())
	{
		SubPtr next = mActive->pop();

		// 1. Check to see if the subproblem can be pruned
		// 2. Check to see if the subproblem is terminal (and update incumbent)
		// 3. Generate children if neither 1 or 2

		auto children = next->children();
		for (auto child : children) mActive->push(SubPtr(child));

		++mNumExplored;
		printf("Explored %d subproblems\n", mNumExplored);

		testIncumbent(next.get());
	}

	return mIncumbent.get();
}

void Tree::testIncumbent(Subproblem* candidate)
{
	if (mSense == Minimization && candidate->objValue() < mUB)
		mUB = candidate->objValue();
	else if (mSense == Maximization && candidate->objValue() > mLB)
		mLB = candidate->objValue();
	else return;

	// If we get here, then we passed one of the two tests above and need to update
	// our incumbent pointer.  This shouldn't happen very often, so I'm OK just doing
	// a copy instead of dealing with move semantics
	mIncumbent.reset(candidate->clone());
}

};


