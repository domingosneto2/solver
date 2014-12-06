
#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <sat/CNFFitnessEvaluator.h>

#define INT_BITSIZE (sizeof(int)*8)

//-----------------------------------------------------------------------------
CNFFitnessEvaluator *CNFFitnessEvaluator::create()
{
	return new CNFFitnessEvaluator();
}
//-----------------------------------------------------------------------------
void CNFFitnessEvaluator::release()
{
	delete this;
}
//-----------------------------------------------------------------------------
CNFFitnessEvaluator::CNFFitnessEvaluator()
{
	previous = NULL;
	current = NULL;
}
//-----------------------------------------------------------------------------
CNFFitnessEvaluator::~CNFFitnessEvaluator()
{
	if (current) delete[] current;
	if ( previous ) delete[] previous;
}
//-----------------------------------------------------------------------------
/**
 * Set the formula that will be used to evaluate
 * the fitness of an individual.
 */
void CNFFitnessEvaluator::setFormula( const CNFFormula &other )
{
	formula = other;
	stringSize = formula.getNumVars();
	arraySize = ( stringSize + INT_BITSIZE - 1 )/ INT_BITSIZE;	
}
//-----------------------------------------------------------------------------
/**
 * Here we evaluate the fitness of an individual.
 */
double CNFFitnessEvaluator::evaluate( void *individual )
{
    // We store the last evaluated individual in a
    // cache.  This way, if the new individual is a copy
    // of the last one (wich usually happens after a number
    // of generations, when the population converges), we will
    // save a lot of time by not having to re-evaluate everything.
    // Here we are checking wether this individual is equal to
    // the last one.
	if ( previous != NULL )
	{
	    // Copy the individual to a buffer.
		memcpy( current, individual, arraySize );
		// zero-out the remaining bits of the last byte, just to be sure that 
		// the unused bits won't make the memcmp call fail
		int lastBits = stringSize % INT_BITSIZE;
		if ( lastBits > 0 )
		{
			int pattern = ( 1 << lastBits ) - 1;
			current[arraySize - 1] &= pattern;
		}

        // Compare the current individual with the last one in the cache
        // If they are the same we return the stored evaluation.
		if ( memcmp( current, previous, arraySize ) == 0 )
		{		    
			// cout << "Cache hit!" << endl;
			return lastEval;
		}
	}
	else
	{
		current = new int[arraySize];
		previous = new int[arraySize];
	}

	
    // Copy the current individual to the cache.
    // We zero-out the remaining bits of the last byte, just to be sure
    // that the unused bits won't make the comparision fail.
	memcpy( previous, individual, arraySize );
	int lastBits = stringSize % INT_BITSIZE;
	if ( lastBits > 0 )
	{
		int pattern = ( 1 << lastBits ) - 1;
		current[arraySize - 1] &= pattern;
	}

    // Now let's evaluate this individual.  We need an interpretation
    // object that will wrap the actual bits.
	Interpretation interpretation( stringSize );
	interpretation.assign( individual, stringSize );
	
	// Get the number of satisfied clauses.
	int nSatisfied = 0;
	for ( int i = 0; i < formula.getNumClauses(); i++ )
	{
		if ( formula.getClauseValue( i, interpretation ) == true )
		{
			nSatisfied++;
		}
	}

    // If this individual has all clauses satisfied, we set a flag
    // indicating that it is the result.
	if ( nSatisfied == formula.getNumClauses() )
	{
		bLastIsResult = true;
	}
	else
	{
		bLastIsResult = false;
	}
	
	// Save the number of satisfied clauses in the cache.
	lastEval = nSatisfied;
	
	// The number of satisfied clauses is this individual's fitness.
	double fitness = nSatisfied;
	return fitness;
}
//-----------------------------------------------------------------------------
bool CNFFitnessEvaluator::lastIsResult()
{
	return bLastIsResult;
}
//-----------------------------------------------------------------------------
