// bnbtree.cpp: (c) David R. Morrison, July 2014
// Implementation details for the branch-and-bound tree class

#include "bnbtree.h"
#include "subproblem.h"
#include "search.h"

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

namespace BnB
{

SearchStrategy::~SearchStrategy() { }

Tree::Tree(Subproblem* root, SearchStrategy* searcher, const Sense& sense) :
	mSense(sense),
	mNextId(0),
	mActive(searcher),
	mIncumbent(nullptr),
	mNumExplored(0),
	mTreeSize(1),	// There's always a root
	mCpuTicks(0)
{
	mActive->push(SubPtr(root));
	storeBound(root);
}

Status Tree::explore(size_t nlim, int tlim, int outputFreq)
{
	Status status = Running;
	clock_t start = clock();
	size_t startNodes = mNumExplored;

    printf("   iter  size  curr    lb    ub   gap\n");
	while (true)	// Do termination checks at the end so status can be set correctly
	{
		// Get the next subproblem to explore from the set of active subproblems
		SubPtr next = mActive->pop();

		// Generate children; it's up to the subproblem to do any and all pruning
		// tests to determine which children and how many children to generate.  A
		// path in the tree terminates IFF the subproblem returns no children.
		auto children = next->children(LB(), UB());
		for (auto child : children) 
		{
			mActive->push(SubPtr(child));
			storeBound(child);
			child->mId = mNextId++;
		}

		// If $next is better than the incumbent, update $mIncumbent
		updateIncumbent(next.get());	
		delBound(next.get());

		// Update stats and print progress 
		mTreeSize += children.size(); ++mNumExplored;
		if (mNumExplored % outputFreq == 0)
			printProgress(next.get(), false);
		
		// Terminate the algorithm if we've explored the entire tree, if the incumbent equals 
		// the bound, if we've exceeded the node limit, or if we've exceeded the time limit
		if (mActive->empty()) { status = mIncumbent ? Optimal : Infeasible; break; }
		if (gapClosed()) { status = Optimal; break;	}
		if (nlim != -1 && mNumExplored > nlim + startNodes) { status = NodeLimReached; break; }
		if (tlim != -1 && (clock() - start) / CLOCKS_PER_SEC > tlim) 
			{ status = TimeLimReached; break; }
	}

	mCpuTicks += clock() - start;
	printStats(status);

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
	return false;
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
	return (UB() - LB()) / UB();
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
	printf("%5lu %5lu %5lu %5.2f %5.2f %5.2f; ",
			mNumExplored,
			mActive->size(),
			s->id(),
			LB(),
			UB(),
			gap());
	if (s) s->print();
	printf("\n");
}	

void Tree::printStats(Status status) const
{
	printf("\nTime: %0.2fs; Nodes explored: %ld; Total tree size: %ld\n", mCpuTicks / (double)CLOCKS_PER_SEC, mNumExplored, mTreeSize);
	printf("Status: ");
	switch (status)
	{
		case Optimal: printf("Optimal"); break;
		case Infeasible: printf("Infeasible"); break;
		case NodeLimReached: printf("Node limit reached"); break;
		case TimeLimReached: printf("Time limit reached"); break;
		case Running: printf("Running"); break;
		default: printf("Unknown"); break;
	}
	if (mIncumbent)
	{
		printf("; Incumbent value: %0.2f\n", mIncumbent->objValue());
		printf("Incumbent: ");
		mIncumbent->print();
		printf("\n");
	}
	else printf("\n");
	printf("\n");
}


};


