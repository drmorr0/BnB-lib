#ifndef DFS_H
#define DFS_H

namespace BnB
{

class DFS : public SearchContainer
{
public:
    void push(const BnB::Subproblem& s) { mSubproblems.push_back(s); }
    BnB::Subproblem pop() { auto s = mSubproblems.back(); mSubproblems.pop_back(); return s; }
    bool empty() { return mSubproblems.empty(); }

private:
    vector<BnB::Subproblem> mSubproblems;
};

};

#endif // DFS_H



