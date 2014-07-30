// bnbtree.cpp: (c) David R. Morrison, July 2014
// Implementation details for the branch-and-bound tree class

#include "bnbtree.h"
#include "subproblem.h"
#include "search.h"

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
		for (auto child : children) 
		{
			mActive->push(SubPtr(child));

			// Update the stored bounds used for calculating the gap; it's 
			// conceivable that the child bound could change between when it's
			// generated and when it's explored, so we need to keep track of 
			// the original bound which we stored
			child->mStoredBound = child->bound();
			++mBounds[child->mStoredBound];
		}

		++mNumExplored;
		printf("Explored %d subproblems\n", mNumExplored);

		// Update our set of bounds; if no subproblems remain with this particular
		// bound, we can remove that bound from our set (and potentially close the gap)
		auto el = mBounds.find(next->mStoredBound); --(el->second);
		if (el->second == 0) mBounds.erase(el);

		updateIncumbent(next.get());	// If $next is better than the incumbent, update $mIncumbent
		if (gapClosed()) break;			// Terminate the algorithm if the incumbent equals the bound
	}

	return mIncumbent.get();
}

void Tree::updateIncumbent(Subproblem* candidate)
{
	// Make sure the candidate is a complete solution; if not, do nothing
	if (!candidate->isTerminal()) return;

	// Check if the new solution is better than our current incumbent; there are three cases:
	// 1. We don't have a current incumbent (store the candidate unconditionally)
	// 2. We're minimizing (store the candidate if its value is smaller than our incumbent's)
	// 3. We're maximizing (store the candidate if its value is larger than our incumbent's)
	if ((!mIncumbent) ||
		(mSense == Minimization && candidate->objValue() < mIncumbent->objValue()) ||
		(mSense == Maximization && candidate->objValue() > mIncumbent->objValue()))
	{ mIncumbent.reset(candidate->clone()); }
}

bool Tree::gapClosed() const
{
	if (!mIncumbent) return false;

	double bound = (mSense == Minimization) ? mBounds.begin()->first : mBounds.rbegin()->first;
	if (fabs(bound - mIncumbent->objValue()) < Tolerance)
		return true;
	else return false;
}

double Tree::getLB() const
{
	if (mSense == Minimization) 
		return (mBounds.begin() == mBounds.end()) ? NegInf : mBounds.begin()->first;
	else return (mIncumbent) ? mIncumbent->objValue() : NegInf;
}

double Tree::getUB() const
{
	if (mSense == Minimization)
		return (mIncumbent) ? mIncumbent->objValue() : PosInf;
	else return (mBounds.rbegin() == mBounds.rend()) ? PosInf : mBounds.rbegin()->first;
}


};


