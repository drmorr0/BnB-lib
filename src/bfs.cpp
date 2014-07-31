// bfs.cpp: (c) David R. Morrison, July 2014
// Implementation details for the best-first search strategy

#include "bfs.h"
#include "subproblem.h"

using namespace std;

namespace BnB
{

void BFS::push(SubPtr&& s) 
{ 
	double mu = ((BfsSubproblem*)s.get())->mu();
	mSubproblems.emplace(mu, move(s)); 
}

SubPtr BFS::pop() 
{ 
	auto iter = mSubproblems.begin();
	SubPtr s = move(iter->second);
	mSubproblems.erase(iter);
	return s; 
}

bool BFS::empty() const { return mSubproblems.empty(); }

size_t BFS::size() const { return mSubproblems.size(); }

};

