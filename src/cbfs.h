#ifndef CBFS_H
#define CBFS_H
/*
 * cbfs.h: (c) David R. Morrison, July 2014
 *
 * The cyclic best-first search (CBFS) strategy to be used with the branch-and-bound tree solver;
 * implements CBFS using a map from contour index to a sub-map of subproblems.  The position in
 * the contour list is tracked with an iterator into first map.
 */

#include "search.h"
#include "bfs.h"

#include <memory>
#include <vector>
#include <map>

namespace BnB
{

class CbfsSubproblem : public BfsSubproblem
{
public:
	virtual long contour() = 0;
};

class CBFS : public SearchStrategy
{
public:
	CBFS();
    void push(SubPtr&& s);
    SubPtr pop(); 
    bool empty() const;
	size_t size() const;

private:
	std::map<int, Contour> mContours;
	std::map<int, Contour>::iterator mCurrContour;
	size_t mNumSubproblems;
};

};

#endif // CBFS_H



