
#ifndef _CSP_GENETIC_SOLVER_EXTRA_DATA_H_
#define _CSP_GENETIC_SOLVER_EXTRA_DATA_H_

#include <csp/CSPProblem.h>
#include <ga/GeneticSolver.h>

//---------------------------------------------------------------------------
/**
 * A class that will store a copy of a CSP problem that will be shared
 * by the CSP Genetic Solver related classes.
 */
class CSPGeneticSolverExtraData : public GeneticSolverExtraData
{
	public:
	static CSPGeneticSolverExtraData *create( CSPProblem *problem );
	virtual void release();


	private:
	CSPGeneticSolverExtraData( CSPProblem *problem );
	~CSPGeneticSolverExtraData();
	CSPProblem *problem;
};
//---------------------------------------------------------------------------

#endif

