#ifndef BNBTREE_H
#define BNBTREE_H
/*
 * bnbtree.h: David R. Morrison, July 2014
 *
 * A class for maintaining a branch-and-bound search tree for an arbitrary optimization problem; the
 * class is extensible by providing custom lower bound functions, branching strategies, and search
 * strategies.  Extensions such as branch-and-price (B&P) and branch-and-cut (B&C) are also
 * supported.
 *
 */

class BnBTree
{
public:
	BnBTree();

private:
};

#endif // BNBTREE_H



