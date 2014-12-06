
#ifndef _CNF_FITNESS_EVALUATOR_H_
#define _CNF_FITNESS_EVALUATOR_H_

#include <ga/GeneticSolver.h>
#include <sat/CNFFormula.h>

//-----------------------------------------------------------------------------
/**
 * This is the class that evaluates the fitness of an individual
 * for the SAT genetic algorithm.
 */
class CNFFitnessEvaluator : public FitnessEvaluator
{
	public:
	static CNFFitnessEvaluator *create();
	virtual void release();

	void setFormula( const CNFFormula &other );
	
	virtual double evaluate( void *individual );
	virtual bool lastIsResult();

	private:
	CNFFitnessEvaluator();
	~CNFFitnessEvaluator();

	CNFFormula formula;
	bool bLastIsResult;
	int stringSize;

	int *previous;
	int *current;
	int arraySize;
	int lastEval;
};
//-----------------------------------------------------------------------------

#endif

