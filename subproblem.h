#ifndef SUBPROBLEM_H
#define SUBPROBLEM_H
/*
 * subproblem.h: (c) David R. Morrison, July 2014
 *
 * A class implementing a subproblem for a branch-and-bound (or derivative) search tree
 */

#include <vector>
using std::vector;

namespace BnB
{

class Subproblem
{
public:
	Subproblem(int d = 0) : mDepth(d) { }
	vector<Subproblem> children()
	{
		if (mDepth > 5) return vector<Subproblem>();
		else return vector<Subproblem>{Subproblem(mDepth + 1), Subproblem(mDepth + 1)};
	}

private:
	int mDepth;
};

};

#endif // SUBPROBLEM_H
