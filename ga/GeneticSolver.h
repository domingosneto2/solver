
#ifndef _GENETIC_SOLVER_H_
#define _GENETIC_SOLVER_H_

//-----------------------------------------------------------------------------
/**
 * A pluggable object that evaluates the fitness of a given chromossome.
 * By using pluggable objects, the GeneticSolver class can be used
 * as a generic genectic solver.
 */
class FitnessEvaluator
{
	public:
	virtual void release() = 0;

	virtual double evaluate( void *individual ) = 0;
	virtual bool lastIsResult() = 0;
};
//-----------------------------------------------------------------------------
/**
 * A pluggable object that can be used to improve each chromossome by local
 * search.  Using this object is optional.
 */
class ChromossomeImprover
{
	public:
	virtual void release() = 0;

	virtual void improve( void *individual ) = 0;
};
//-----------------------------------------------------------------------------
/**
 * A pluggable object that performs the default genetic operations.
 *
 * This is required for each specific GA implementation.
 */
class GeneticOperators
{
	public:
	virtual void release() = 0;

	virtual void *allocateIndividual() = 0;
	virtual void *initializeRandomIndividual( void *individual ) = 0;
	virtual void releaseIndividual( void *individual ) = 0;
	virtual void *copyIndividual( void *src ) = 0;
	virtual void  copyIndividual( void *src, void *dest ) = 0;

	virtual void crossover( void *individual1, void *individual2, void *dest1, void *dest2 ) = 0;
	virtual void mutate( void *individual ) = 0;
};
//-----------------------------------------------------------------------------
/**
 * A placeholder for any extra data that a specific GA may need.
 */
class GeneticSolverExtraData
{
	public:
	virtual void release() = 0;
};
//-----------------------------------------------------------------------------
/**
 * Represents a population and it's generations.
 *
 * This class allows an extension to the genetic algorithm to enable it
 * to run on multiple simultaneous populations.  We still don't know if it
 * improves or degrades performance.
 */
class Population
{
	public:
	Population();
	~Population();

	void setId( int id );
	void setPopulationSize( int n );
	void setFitnessEvaluator( FitnessEvaluator *evaluator );
	void setChromossomeImprover( ChromossomeImprover *improver );
	void setGeneticOperators( GeneticOperators *operators );

	void setScale( bool scale );
	void setMaxFitnessScale( double scale );
	void setElitist( bool _elitist );
	
	void init();
	void release();

	bool step();

	void *getResult();

	void * getBestIndividual();

	double getMaxRawFitness();

	private:
	int id;
	int populationSize;
	FitnessEvaluator *evaluator;
	ChromossomeImprover *improver;
	GeneticOperators *operators;
	void *result;
	bool bScale;
	double scaleFactor;
	double maxRawFitness;
	bool elitist;

	// points to the best individual of the population
	// this field is used if the elitist option is set
	void *previousBestIndividual;
	void *currentBestIndividual;
	double previousBestFitness;
	double currentBestFitness;

	// a copy of the overall best individual.
	// this field is used by the getBestIndividual method.
	void *overallBestIndividual;
	double overallBestFitness;

	// Those fields are updated by the calculateCurPopulationFitness method
	// previous values are lost after a call to this method
	double fitnessAcc, maxFitness, minFitness;
	
	// Current an next populations
	void **cur;
	void **next;

	double *fitness;
	double *fitnessNext;

	void initPopulation( void **population );
	void **allocPopulation();	

	int pickIndividual( double *fitness, double random );

	void improve ( void *individual );

	void deletePopulation( void **pop );

	void getScalingCoefficients( double avgFitness, double maxFitness, double minFitness, double &a, double &b );

	bool evaluateIndividualFitness( void **pop, double *fitnessVector, int individual );
	void updateStatistics( void **pop, double *fitnessVector, int individual );


	int curStep;
};
//-----------------------------------------------------------------------------
/**
 * This is the generic genetic solver.
 *
 * To use it, you must create a GeneticSolver object and then plug on it 
 * the objets that will enable it to solve specific instances of the problem.
 * For example, there are pluggable objects to solve SAT problems and
 * pluggable objects to resolve CSPs.  Other pluggable objects can be created.
 *
 * At least, you need objects that implement the FitnessEvaluator and 
 * GeneticOperator interfaces.
 * 
 */
class GeneticSolver
{
	public:
	static GeneticSolver *create();
	void release();

    // Configuration methods.
	void setNumPopulations( int numPopulations );
	void setPopulationSize( int populationSize );
	void setScale( bool scale );
	void setMaxFitnessScale( double scale );
	
	// Pluggable objects setting.
	void setFitnessEvaluator( FitnessEvaluator *evaluator );
	void setChromossomeImprover( ChromossomeImprover *improver );
	void setGeneticOperators( GeneticOperators *operators );
	void setExtraData( GeneticSolverExtraData *extraData );
	GeneticSolverExtraData *getExtraData();

	void setElitist( bool elitist );

    // Solving
	bool solve( int maxGenerations );

	void *getResult();


	void *getBestIndividual();

	int getNumSteps();

	double getMaxRawFitness();

	private:
	GeneticSolver();
	~GeneticSolver();
    void retrieveOverallBestIndividual( Population *pop );

	int numPopulations;
	int populationSize;

	FitnessEvaluator *evaluator;
	ChromossomeImprover *improver;
	GeneticOperators *operators;
	GeneticSolverExtraData *extraData;

	double mutationProbability;
	
	bool bScale;
	double scaleFactor;
	int numSteps;
	double maxRawFitness;

	bool elitist;

	void *result;
	void *bestIndividual;
};
//-----------------------------------------------------------------------------

#endif

