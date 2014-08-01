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
	storeBound(root);
}

Status Tree::explore(size_t nlim, int tlim, int outputFreq)
{
	Status status = Running;
	clock_t start = clock();
	size_t startNodes = mNumExplored;
	while (!mActive->empty())
	{
		// Get the next subproblem to explore from the set of active subproblems
		SubPtr next = mActive->pop();

		// Generate children; it's up to the subproblem to do any and all pruning
		// tests to determine which children and how many children to generate.  A
		// path in the tree terminates IFF the subproblem returns no children.
		auto children = next->children();
		for (auto child : children) 
		{
			mActive->push(SubPtr(child));
			storeBound(child);
		}

		++mNumExplored;
		
		// If $next is better than the incumbent, update $mIncumbent
		updateIncumbent(next.get());	
		delBound(next.get());

		// Print progress 
		if (mNumExplored % outputFreq == 0)
			printProgress(next.get(), false);
		
		// Terminate the algorithm if the incumbent equals the bound, if we've exceeded the
		// node limite, or if we've exceeded the time limit
		if (gapClosed()) break;	
		if (nlim != -1 && mNumExplored > nlim + startNodes) { status = NodeLimReached; break; }
		if (tlim != -1 && (clock() - start) / CLOCKS_PER_SEC > tlim) 
			{ status = TimeLimReached; break; }
	}

	if (status == Running)
		status = mIncumbent ? Optimal : Infeasible;

	return status;
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
	{ 
		delBound(mIncumbent.get());
		mIncumbent.reset(candidate->clone()); 
		storeBound(mIncumbent.get());
		printProgress(mIncumbent.get(), true);
	}
}

bool Tree::gapClosed() const
{
	if (!mIncumbent) return false;

	double bound = (mSense == Minimization) ? mBounds.begin()->first : mBounds.rbegin()->first;
	if (fabs(bound - mIncumbent->objValue()) < Tolerance)
		return true;
	else return false;
}

double Tree::LB() const
{
	if (mSense == Minimization) 
		return (mBounds.begin() == mBounds.end()) ? NegInf : mBounds.begin()->first;
	else return (mIncumbent) ? mIncumbent->objValue() : NegInf;
}

double Tree::UB() const
{
	if (mSense == Minimization)
		return (mIncumbent) ? mIncumbent->objValue() : PosInf;
	else return (mBounds.rbegin() == mBounds.rend()) ? PosInf : mBounds.rbegin()->first;
}

double Tree::gap() const
{
	return (UB() - LB()) / LB();
}

void Tree::storeBound(Subproblem* s)
{
	if (!s) return;

	// Update the stored bounds used for calculating the gap; it's 
	// conceivable that the child bound could change between when it's
	// generated and when it's explored, so we need to keep track of 
	// the original bound which we stored
	s->mStoredBound = s->bound();
	++mBounds[s->mStoredBound];
}

void Tree::delBound(Subproblem* s)
{
	if (!s) return;

	// Update our set of bounds; if no subproblems remain with this particular
	// bound, we can remove that bound from our set (and potentially close the gap)
	auto el = mBounds.find(s->mStoredBound); 
	if (el == mBounds.end()) 
		{ fprintf(stderr, "Bound = %0.2f not stored!\n", s->mStoredBound); exit(-1); }

	--(el->second);
	if (el->second == 0) mBounds.erase(el);
	else if (el->second < 0) 
		{ fprintf(stderr, "Bound = %0.2f has negative stored subproblems!\n", s->mStoredBound); exit(-1); }
}

void Tree::printProgress(Subproblem* s, bool newIncumbent) const
{
	if (newIncumbent) printf("* ");
	else printf("  ");
	printf("%5lu %5lu %5.2f %5.2f %5.2f; ",
			mNumExplored,
			mActive->size(),
			LB(),
			UB(),
			gap());
	if (s) s->print();
	printf("\n");
}	


};


