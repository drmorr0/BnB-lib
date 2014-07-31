// cbfs.cpp: (c) David R. Morrison, July 2014
// Implementation details for the cyclic best-first search strategy

#include "cbfs.h"
#include "subproblem.h"

using namespace std;

namespace BnB
{

CBFS::CBFS() :
	mNumSubproblems(0)
{
	// Instantiate an empty contour and set our iterator to point at it
	mContours[0];
	mCurrContour = mContours.begin();
}

void CBFS::push(SubPtr&& s) 
{ 
	// Insert the new subproblem into the contour structure 
	CbfsSubproblem* ss = (CbfsSubproblem*)s.get();
	double mu = ss->mu();
	long contour = ss->contour();
	mContours[contour].emplace(mu, move(s));

	++mNumSubproblems;
}

SubPtr CBFS::pop() 
{ 
	// Advance the contour index; empty contours act as a placeholder for our current
	// contour index -- we want to keep track of where we were, even if there's nothing
	// there now.  This will allow us to insert new things and maintain the appropriate
	// ordering.  Therefore, we only delete empty contours once we move off of them.
	//
	// It should never be the case that there is more than one empty contour in the contour
	// list, and if there is an empty contour, the current contour interator should be
	// pointing at it at the start of pop.  Then, deleting the empty contour will advance
	// mCurrContour to the next element in the list.  Otherwise, we must do the advance 
	// manually.
	if (mCurrContour->second.empty())
	{
		mCurrContour = mContours.erase(mCurrContour);
	}
	else ++mCurrContour;
	
	// Cycle back to the beginning
	if (mCurrContour == mContours.end()) mCurrContour = mContours.begin();

	// Get the subproblem minimizing mu
	auto iter = mCurrContour->second.begin();
	SubPtr s = move(iter->second);
	mCurrContour->second.erase(iter);

	--mNumSubproblems;

	return s; 
}

bool CBFS::empty() const { return mNumSubproblems == 0; }

size_t CBFS::size() const { return mNumSubproblems; }

};

