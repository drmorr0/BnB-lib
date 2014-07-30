#ifndef DFS_H
#define DFS_H
/*
 * dfs.h: (c) David R. Morrison, July 2014
 *
 * The depth-first search (DFS) strategy to be used with the branch-and-bound tree solver;
 * implements DFS using a vector as a stack.
 */

#include "search.h"

#include <vector>

namespace BnB
{

class DFS : public SearchStrategy
{
public:
    void push(SubPtr&& s);
    SubPtr pop(); 
    bool empty() const;

private:
	std::vector<SubPtr> mSubproblems;
};

};

#endif // DFS_H



