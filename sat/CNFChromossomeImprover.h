
#ifndef _CNF_CHROMOSSOME_IMPROVER_H_
#define _CNF_CHROMOSSOME_IMPROVER_H_

#include <ga/GeneticSolver.h>
#include <sat/CNFFormula.h>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
/**
 * The chromossome improver for SAT Genetic Algorithm.
 *
 * This class is called by the GeneticSolver on every individual
 * of the population.  It performs a local search in an attempt to improve
 * the fitness of the individual.
 */
class CNFChromossomeImprover : public ChromossomeImprover
{
	public:
	static CNFChromossomeImprover *create();
	virtual void release();	
	
	void setFormula( const CNFFormula &other );
	virtual void improve( void *individual );
	
	
	void useQuickLoop( bool bQuickLoop );
	void useCache( bool bCache );
	void usePermutation( bool bPermutation );
	void flipOnStrictImprove( bool bStrictFlip );

	private:
	CNFChromossomeImprover();
	~CNFChromossomeImprover();

	void mode3( void *individual );

	void initMode3();

	bool improveFromCache( void *individual );

	bool bQuickLoop;
	bool bCache;
	bool bPermutation;
	bool bStrictFlip;

	CNFFormula formula;
	int mode;
	bool mode3Init;

	int *previous;
	int *previousRes;
	int *current;

	int stringSize;
	int arraySize;

	vector< vector< int > > variableClauses;
	vector< int > permutation;
};

#endif

