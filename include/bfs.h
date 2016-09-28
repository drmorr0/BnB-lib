#ifndef BFS_H
#define BFS_H
/*
 * bfs.h: (c) David R. Morrison, July 2014
 *
 * The best-first search (BFS) strategy to be used with the branch-and-bound tree solver;
 * implements BFS using a map from measure-of-best (mu) to subproblems
 */

#include "search.h"
#include "subproblem.h"

#include <memory>
#include <vector>
#include <map>

namespace BnB
{

// Borrow the contour terminology from CBFS; BFS just has one contour
typedef std::multimap<double, SubPtr> Contour;

class BfsSubproblem : public Subproblem
{
public:
	virtual double mu() = 0;
};


class BFS : public SearchStrategy
{
public:
    void push(SubPtr&& s);
    SubPtr pop(); 
    bool empty() const;
	size_t size() const;

private:
	Contour mSubproblems;
};

};

#endif // BFS_H



