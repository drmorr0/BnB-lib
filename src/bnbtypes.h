#ifndef BNBTYPES_H
#define BNBTYPES_H
/*
 * bnbtypes.h: (c) David R. Morrison, July 2014
 *
 * Types and enums used in the branch-and-bound code
 */

#include <limits>
#include <memory>

namespace BnB
{

class Subproblem;

typedef std::unique_ptr<Subproblem> SubPtr;
const double PosInf = std::numeric_limits<double>::infinity();
const double NegInf = -PosInf;
const double Tolerance = 10e-7;

enum Sense { Minimization, Maximization };

};

#endif // BNBTYPES_H
