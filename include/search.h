#ifndef SEARCH_H
#define SEARCH_H
/*
 * search.h: (c) David R. Morrison, July 2014
 *
 * Abstract base class for a search strategy in a branch-and-bound algorithm
 */

#include "bnbtypes.h"

namespace BnB
{

class SearchStrategy
{
public:
	virtual ~SearchStrategy() = 0;

	virtual void push(SubPtr&& s) = 0;
	virtual SubPtr pop() = 0;
	virtual bool empty() const = 0;
	virtual size_t size() const = 0;
};

};

#endif // SEARCH_H


