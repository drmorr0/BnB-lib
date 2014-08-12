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

#include <map>
#include <memory>
#include <limits>


namespace BnB
{

class Subproblem;
class SearchStrategy;

class Tree
{
public:
	Tree(Subproblem* root, SearchStrategy* searcher, const Sense& sense);
	Status explore(size_t nlim = -1, int tlim = -1, int outputFreq = 1);
	Subproblem* incumbent() { return mIncumbent.get(); }
	void updateIncumbent(Subproblem* newIncumbent);
	bool gapClosed() const;

	double LB() const;
	double UB() const;
	double gap() const;

private:
	Sense mSense;
	size_t mNextId;

	std::unique_ptr<SearchStrategy> mActive;
	SubPtr mIncumbent;
	std::map<double,int> mBounds;

	void storeBound(Subproblem* s);
	void delBound(Subproblem* s);

public:
	void printProgress(Subproblem* s, bool newIncumbent) const;
	void printStats(Status status) const;

private:
	// Statistics tracking
	size_t mNumExplored, mTreeSize;
	clock_t mCpuTicks;
};

};

#endif // BNBTREE_H



