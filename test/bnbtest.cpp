// bnbtest.cpp: (c) David R. Morrison, July 2014
// Test code for the branch-and-bound library

#include "bnbtree.h"
#include "simple_subproblems.h"
#include "dfs.h"
#include "brfs.h"

#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	BnB::Tree searchTree(new SimpleSubproblem, new BnB::BrFS, BnB::Minimization);
	BnB::Subproblem* best = searchTree.explore();
	printf("The optimal solution is %0.2f\n", best->objValue());
	return 0;
}



