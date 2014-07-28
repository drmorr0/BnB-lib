#ifndef DFS_H
#define DFS_H

#include "bnbtree.h"

#include <cstdio>
#include <utility>

namespace BnB
{

class DFS : public SearchStrategy
{
public:
    void push(Subproblem* s) { mSubproblems.push_back(SubPtr(s)); }
    SubPtr pop() 
		{ SubPtr s = std::move(mSubproblems.back()); mSubproblems.pop_back(); return s; }
    bool empty() const { return mSubproblems.empty(); }

private:
	std::vector<SubPtr> mSubproblems;
};

};

#endif // DFS_H



