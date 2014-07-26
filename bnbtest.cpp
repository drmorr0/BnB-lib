// bnbtest.cpp: (c) David R. Morrison, July 2014
// Test code for the branch-and-bound library

#include "bnbtree.h"
#include "dfs.h"

#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	BnB::Tree searchTree(BnB::Subproblem(), new BnB::DFS);
	searchTree.explore();
	return 0;
}



