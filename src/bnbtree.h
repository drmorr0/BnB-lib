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
	Subproblem* explore();
	void updateIncumbent(Subproblem* newIncumbent);
	bool gapClosed() const;

	double LB() const;
	double UB() const;
	double gap() const;

private:
	std::unique_ptr<SearchStrategy> mActive;
	size_t mNumExplored;

	Sense mSense;

	SubPtr mIncumbent;
	std::map<double,int> mBounds;

	void storeBound(Subproblem* s);
	void delBound(Subproblem* s);

public:
	void printProgress(Subproblem* s) const;
};

};

#endif // BNBTREE_H



