
#ifndef _CSP_GENETIC_OPERATORS_H_
#define _CSP_GENETIC_OPERATORS_H_

#include <ga/GeneticSolver.h>
#include <csp/CSPProblem.h>

//---------------------------------------------------------------------------
/**
 * Implements the fitness evaluator for a CSP Genetic algorithm.
 *
 */
class CSPFitnessEvaluator : public FitnessEvaluator
{
	public:
	static CSPFitnessEvaluator *create();
	virtual void release();

	/**
	 * Sets a reference of the problem object.
	 * <p>
	 * This class keeps only a reference to the problem
	 * object and not a copy, so you still have to release
	 * the object when it is no longer necessary.
	 */
	void setProblem( const CSPProblem *problem );

	virtual double evaluate( void *individual );
	virtual bool lastIsResult();

	private:
	CSPFitnessEvaluator();
	~CSPFitnessEvaluator();
	bool bLastIsResult;
	const CSPProblem *problem;
};
//---------------------------------------------------------------------------
/**
 * Implements the genetic operators for a CSP GA.
 */
class CSPGeneticOperators : public GeneticOperators
{
	public:
	static CSPGeneticOperators *create();
	virtual void release();
	
	/**
	 * Sets a reference of the problem object.
	 * <p>
	 * This class keeps only a reference to the problem
	 * object and not a copy, so you still have to release
	 * the object when it is no longer necessary.
	 */
	void setProblem( const CSPProblem *problem );

	void setMutationProbability( double mutationProbability );

	void *allocateIndividual();
	void *initializeRandomIndividual( void *individual );
	void releaseIndividual( void *individual );
	void *copyIndividual( void *src );
	void copyIndividual( void *src, void *dest );

	virtual void crossover( void *individual1, void *individual2, void *dest1, void *dest2 );
	virtual void mutate( void *individual );

	private:
	CSPGeneticOperators();
	~CSPGeneticOperators();

	double mutationProbability;
	const CSPProblem *problem;
};
//---------------------------------------------------------------------------

#endif

