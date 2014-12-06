
#ifndef _CSP_CHROMOSSOME_IMPROVER_H_
#define _CSP_CHROMOSSOME_IMPROVER_H_

#include <ga/GeneticSolver.h>
#include <csp/CSPProblem.h>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
/**
 * The chromossome improver for CSP Genetic Algorithm.
 *
 * This class is called by the GeneticSolver on every individual
 * of the population.  It performs a local search in an attempt to improve
 * the fitness of the individual.
 */
class CSPChromossomeImprover : public ChromossomeImprover
{
	public:
	static CSPChromossomeImprover *create();
	virtual void release();

	void setProblem( CSPProblem *problem );
	virtual void improve( void *individual );
	
	
	void useQuickLoop( bool bQuickLoop );	
	void usePermutation( bool bPermutation );
	void changeOnStrictImprove( bool bStrictFlip );

	private:
	CSPChromossomeImprover();
	~CSPChromossomeImprover();

	void init();
	int getNumVariableSatisfiedConstraints( int var, CSPInterpretation *interpretation );
	bool bQuickLoop;
	bool bPermutation;
	bool bStrictFlip;

	CSPProblem *problem;

	int numVariables;

	bool bInit;

	vector< int > permutation;
	vector< vector< int > > variableConstraints;
};

#endif

