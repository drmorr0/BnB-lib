#ifndef BRFS_H
#define BRFS_H
/*
 * brfs.h: (c) David R. Morrison, July 2014
 *
 * The breadth-first search (BrFS) strategy to be used with the branch-and-bound tree solver;
 * implements BrFS using a vector as a stack.
 */

#include "search.h"

#include <list>

namespace BnB
{

class BrFS : public SearchStrategy
{
public:
    void push(SubPtr&& s);
    SubPtr pop(); 
    bool empty() const;
	size_t size() const;

private:
	std::list<SubPtr> mSubproblems;
};

};

#endif // BRFS_H



