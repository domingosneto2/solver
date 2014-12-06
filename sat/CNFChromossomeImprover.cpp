#include <stdio.h> // for #define NULL
#include <stdlib.h>
#include <memory.h>

#include <sat/CNFChromossomeImprover.h>
#include <util/Random.h>
#define INT_BITSIZE (sizeof(int)*8)

//-----------------------------------------------------------------------------
CNFChromossomeImprover *CNFChromossomeImprover::create()
{
	return new CNFChromossomeImprover();
}
//-----------------------------------------------------------------------------
void CNFChromossomeImprover::release()
{
	delete this;
}
//-----------------------------------------------------------------------------
/** 
 * Constructor, here we initialize some variables.
 */
CNFChromossomeImprover::CNFChromossomeImprover()
{
	mode = 1;
	previous = current = previousRes = NULL;
	mode3Init = false;

	bQuickLoop = false;
	bCache = false;
	bPermutation = true;
	bStrictFlip = false;
}
//-----------------------------------------------------------------------------
CNFChromossomeImprover::~CNFChromossomeImprover()
{
	if ( previous )
	{
		delete[] previous;
	}
	if ( current )
	{
		delete[] current;
	}
	if ( previousRes )
	{
		delete[] previousRes;
	}
}
//-----------------------------------------------------------------------------
/**
 * Sets the formula that will be used to calculate and interpretation's fitness.
 */
void CNFChromossomeImprover::setFormula( const CNFFormula &other )
{
	formula = other;
	// String size is the number of variables in the formula.
	// ArraySize is the number of integers required to represent the formula.
	// Remember that each integer stores 32 bits, so one integer can
	// store the value of 32 variables.
	stringSize = formula.getNumVars();
	arraySize = stringSize / INT_BITSIZE;
	if ( stringSize % INT_BITSIZE != 0 )
	{
		arraySize++;
	}
	
	// We still didn't initialize the improver.
	// It will be initialize in the first time it performs a local search.
	mode3Init = false;
}
//-----------------------------------------------------------------------------
/**
 * If true, only one step of the loop will be performed
 */
void CNFChromossomeImprover::useQuickLoop( bool _bQuickLoop )
{
	bQuickLoop = _bQuickLoop;
}
//-----------------------------------------------------------------------------
/**
 * If true, a caching will be used.  Whenever an input
 * individual is in the cache, the output will be quickly
 * recovered from there, without the need to run the local
 * search again.
 *
 * Currently, the cache stores only the last individual processed,
 * so it's barely usable.
 */
void CNFChromossomeImprover::useCache( bool _bCache )
{
	bCache = _bCache;
}
//-----------------------------------------------------------------------------
/**
 * If true, when iterating over the variables, the algorithm
 * will use a random permutation to chose the order in wich
 * the variables will be tested.
 */
void CNFChromossomeImprover::usePermutation( bool _bPermutation )
{
	bPermutation = _bPermutation;
}
//-----------------------------------------------------------------------------
/**
 * If true, a variable value will only be flipped if the 
 * flip makes the number of satisfied clauses improve.
 * If false, the variable will be flipped even if the
 * number of satisfied clauses stays the same.
 */
void CNFChromossomeImprover::flipOnStrictImprove( bool _bStrictFlip )
{
	bStrictFlip = _bStrictFlip;
}
//-----------------------------------------------------------------------------
/**
 * Here we run a local search on the individual in order to improve it.
 */
void CNFChromossomeImprover::improve( void *individual )
{
    // Perform a one time initialization, if this is
    // the first time we are calling this function.
	if ( mode3Init == false )
	{
		initMode3();
	}

    // If we are using the cache, try to improve from there first.
	if ( bCache )
	{
		if ( improveFromCache( individual ) )
		{
			return;
		}
	}

    // Create an interpretation object that will
    // store the individual.  An individual in the SAT genetic algorithm
    // is an array of integers where each bit is a SAT variable.
	Interpretation interpretation( 1 );	
	interpretation.assign( individual, stringSize );

    // If we are configure to use a random permutation, we create it now.
	if ( bPermutation )
	{
		for ( int k2 = 0; k2 < stringSize - 1; k2++ )
		{
			int len = stringSize - k2 - 1;
			int random = Random::s_urand() % len + k2 + 1;
			int aux = permutation[k2];			
			permutation[k2] = permutation[random];
			permutation[random] = aux;
		}
	}
	

    // Get the number of clauses of the formula.
	int numClauses = formula.getNumClauses();

    // Store here the number of satisfied clauses.
	int satisfied = 0;

    // We will stay in the loop as long as the fitness is improved.
	bool improved = true;

	while ( improved )
	{
		improved = false;
	
	    // For each variable in the formula.	
		for ( int i = 0; i < stringSize; i++ )
		{
		    // pick the next variable in the permutation.
		    // If the user didn't ask to use a random permutation,
		    // the 'permutation' vector will contain the variables
		    // in the given order,  that is, permutation[i] will be 
		    // euqual to i.
			int variable = permutation[i];

			// Get the number of clauses where this variable appears
			int numVariableClauses = variableClauses[variable].size();

            // We will calculate the number of satisfied clauses before
            // and after we flip the variable.
            // The 'delta' variable will tell us if the flip increased
            // or decreased the number of satisfied clauses.
			int delta = 0;
			int j;
			for ( j = 0; j < numVariableClauses; j++ )
			{
				const Clause *clause = formula.getClause( variableClauses[variable][j] );
				if ( clause->getValue( interpretation ) == true )
				{
					delta--;
				}
			}
			interpretation.flip( variable );
			for ( j = 0; j < numVariableClauses; j++ )
			{
				const Clause *clause = formula.getClause( variableClauses[variable][j] );
				if ( clause->getValue( interpretation ) == true )
				{
					delta++;
				}
			}

			// If the flip decreases the number of satisfied clauses,
			// we flip the variable back to the original value.
			if ( delta < 0 )
			{
				interpretation.flip( variable );
			}
			// If the flip doesn't change the number of satisfied clauses,
			// but the user configured the bStrictFlip flag, we will
			// flip if back o the original value.
			else if ( delta == 0 && bStrictFlip )
			{
				// In this case we just want to flip if delta > 0
				interpretation.flip( variable );
			}
			// If the flip improves the number of satisfied clauses we will
			// for sure keep the flip.
			else if ( delta > 0 )
			{
				improved = true;
			}

		}

        // If the user asked us to do only one loop we break now.
		if ( bQuickLoop )
		{
			break;
		}
	}

    // If we are using a cache we store this individual in there.
	if ( bCache )
	{
		memcpy( previousRes, individual, arraySize );
	}
}
//-----------------------------------------------------------------------------
bool CNFChromossomeImprover::improveFromCache( void *individual )
{
	if ( previous != NULL )
	{
		memcpy( current, individual, arraySize );
		// zero-out the remaining of the last byte
		int lastBits = stringSize % INT_BITSIZE;
		if ( lastBits > 0 )
		{
			int pattern = ( 1 << lastBits ) - 1;
			current[arraySize - 1] &= pattern;
		}

		if ( memcmp( current, previous, arraySize ) == 0 )
		{
			// cout << "Cache hit!" << endl;
			memcpy( individual, previousRes, arraySize );
			return true;
		}
	}
	else
	{
		current = new int[arraySize];
		previous = new int[arraySize];
		previousRes = new int[arraySize];
	}

	memcpy( previous, individual, arraySize );
	int lastBits = stringSize % INT_BITSIZE;
	if ( lastBits > 0 )
	{
		int pattern = ( 1 << lastBits ) - 1;
		current[arraySize - 1] &= pattern;
	}

	return false;
}
//-----------------------------------------------------------------------------
void CNFChromossomeImprover::initMode3()
{
    // Get the number of clauses of the formula.
	int numClauses = formula.getNumClauses();

    // this is a vector of vectors.
    // Each entry of the variableClauses vector
    // contains a vector with all the clauses caluses where
    // a given variable appears.
	variableClauses.resize( stringSize );

    // For each clause...
	for ( int i = 0; i < numClauses; i++ )
	{
		const Clause *clause = formula.getClause( i );
		int clauseSize = clause->getNumVars();
		// For each variable in this clause...
		for ( int j = 0; j < clauseSize; j++ )
		{
		    // Save the information that this variable appears in this clause.
			variableClauses[clause->getVariableIndex( j )].push_back( i );
		}
	}

    // Create the permutation vector and initialize it with the variables
    // in the correct order.
	permutation.resize( stringSize );

	for ( int k = 0; k < stringSize; k++ )
	{
		permutation[k] = k;
	}

    // If the user asked us to create a random permutation we scramble 
    // the permutation vector.
	if ( bPermutation )
	{
		for ( int k2 = 0; k2 < stringSize; k2++ )
		{
			int aux = permutation[k2];
			int random = Random::s_urand() % stringSize;
			permutation[k2] = permutation[random];
			permutation[random] = aux;
		}
	}

	mode3Init = true;
}
//-----------------------------------------------------------------------------

