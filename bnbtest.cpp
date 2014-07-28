// bnbtest.cpp: (c) David R. Morrison, July 2014
// Test code for the branch-and-bound library

#include "bnbtree.h"
#include "dfs.h"

#include <cstdio>
#include <vector>

using namespace std;

class MySubproblem : public BnB::Subproblem
{
public:
	MySubproblem() : mDepth(0) { }
	Subproblem* clone() const { return new MySubproblem(*this); }

	vector<Subproblem*> children() 
	{
		vector<Subproblem*> c;
		if (mDepth < 5)
		{
			c.push_back(clone()); ++(((MySubproblem*)c.back())->mDepth);
			c.push_back(clone()); ++(((MySubproblem*)c.back())->mDepth);
		}
		return c;
	}

private:
	int mDepth;
};

int main(int argc, char* argv[])
{
	MySubproblem s; 
	BnB::Tree searchTree(s, new BnB::DFS);
	searchTree.explore();
	return 0;
}



