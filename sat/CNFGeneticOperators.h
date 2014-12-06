
#ifndef _CNF_GENETIC_OPERATORS_H_
#define _CNF_GENETIC_OPERATORS_H_

#include <ga/GeneticSolver.h>

//-----------------------------------------------------------------------------
/**
 * This class implements the genetic operators for the SAT genetic algorithm.
 */
class CNFGeneticOperators : public GeneticOperators
{
	public:
	static CNFGeneticOperators *create();
	virtual void release();	

	void *allocateIndividual();
	void releaseIndividual( void *individual );
	void *copyIndividual( void *src );
	void copyIndividual( void *src, void *dest );
	void *initializeRandomIndividual( void *individual );

	void crossover( void *individual1, void *individual2, void *dest1, void *dest2 );
	void mutate( void *individual );

	void setMutationProbability( double mutationProbability );
	void setStringSize ( int stringSize );
	
	private:
	void offspring( int pos, void *parentLeft, void *parentRight, void *offspring );
	CNFGeneticOperators();
	/// The number of variables in each individual (equals to the number of bits in the string)
	int stringSize;
	int individualSize;

	double mutationProbability;

	void setBit( void *individual, int bit, bool value );
	bool getBit( void *individual, int bit );
};
//-----------------------------------------------------------------------------

#endif

