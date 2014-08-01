// bnbtest.cpp: (c) David R. Morrison, July 2014
// Test code for the branch-and-bound library

#include "bnbtree.h"
#include "simple_subproblems.h"
#include "dfs.h"
#include "brfs.h"
#include "bfs.h"
#include "cbfs.h"

#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	BnB::Tree searchTree(new SimpleSubproblem, new BnB::CBFS, BnB::Minimization);
	BnB::Status status = searchTree.explore();
	printf("BnB terminated with status %d; ", status);
	if (searchTree.incumbent()) 
		printf("incumbent value = %0.2f\n", searchTree.incumbent()->objValue());
	else printf("no incumbent found.\n");
	return 0;
}



