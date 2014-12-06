

#ifndef _BASIC_CNF_SOLVER_H_
#define _BASIC_CNF_SOLVER_H_

#include <sat/CNFFormula.h>

//---------------------------------------------------------------------------
/*
 * A depth search solver.
 *
 * This is a very naive solver for SAT problems.  This is included here
 * just as a testbed for our SAT implementation.
 */
class BasicCNFSolver
{
    public:
    void solve( CNFFormula *formula, Interpretation &interpretation );
    
    protected:
    bool search( CNFFormula *formula, Interpretation &interpretation, int curIndex );
};
//---------------------------------------------------------------------------

#endif

