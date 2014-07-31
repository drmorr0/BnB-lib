// dfs.cpp: (c) David R. Morrison, July 2014
// Implementation details for the depth-first search strategy

#include "brfs.h"
#include "subproblem.h"

using namespace std;

namespace BnB
{

void BrFS::push(SubPtr&& s) { mSubproblems.push_back(move(s)); }

SubPtr BrFS::pop() 
{ 
	SubPtr s = move(mSubproblems.front()); 
	mSubproblems.pop_front(); 
	return s; 
}

bool BrFS::empty() const { return mSubproblems.empty(); }

size_t BrFS::size() const { return mSubproblems.size(); }

};

