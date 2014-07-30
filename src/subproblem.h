#ifndef SUBPROBLEM_H
#define SUBPROBLEM_H
/*
 * subproblem.h: (c) David R. Morrison, July 2014
 *
 * A class implementing a subproblem for a branch-and-bound (or derivative) search tree
 */

#include <vector>

namespace BnB
{

class Subproblem
{
public:
	Subproblem() { }
	virtual Subproblem* clone() const = 0;

	virtual std::vector<Subproblem*> children() = 0;

	/* Return the current value of the (partial) solution */
	virtual double objValue() = 0; 

	/* Return true if the subproblem is a complete solution */
	virtual bool isTerminal() = 0; 

	/* 
	 * Return a valid lower (upper) bound for a minimization (maximization) problem;
	 * if your problem doesn't use bounds to prune, you don't need to override the following
	 * function, which always returns infinity.
	 */
	virtual double bound() { return PosInf; }

private:
	friend class Tree;
	double mStoredBound;
};

};

#endif // SUBPROBLEM_H
