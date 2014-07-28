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

};

};

#endif // SUBPROBLEM_H
